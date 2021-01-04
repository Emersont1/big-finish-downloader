#include <libbf/gui/modules/main_window.hpp>

#include <iostream>

int libbf::gui::main_window::update_func(void* d) {
    auto m = (libbf::gui::main_window*) d;

    gtk_progress_bar_set_fraction((GtkProgressBar*) m->progress_bar, m->download_progress);
    gtk_label_set_text((GtkLabel*) m->downloading_status_ii, m->status_ii.c_str());

    if (!m->items_fut.valid() && m->items.size() == 0)
        m->items_fut =
                std::async(std::launch::async, &libbf::gui::main_window::get_items, m, m->cookie);
    if (m->items_fut.valid()) {
        if (m->items_fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            m->items = m->items_fut.get();
            for (auto x = m->items.begin(); x != m->items.end(); ++x) {
                m->add_to_view(*x);
            }
        }
    }

    if (!m->downloader.valid()) {
        auto a = gtk_tree_view_get_model(m->view_downloading);
        GtkTreeIter iter;
        if (gtk_tree_model_get_iter_first(a, &iter)) {
            bool y;
            do {
                int id;
                gtk_tree_model_get(a, &iter, 1, &y, 3, &id, -1);
                if (y) {
                    auto item = std::find_if(m->items.begin(), m->items.end(),
                                             [&](std::pair<libbf::download, GdkPixbuf*> i) {
                                                 return i.first.image_number == id;
                                             });
                    if (item == m->items.end()) {
                        return 1;
                    }

                    m->downloader =
                            std::async(std::launch::async, &libbf::gui::main_window::download, m,
                                       item->first, m->quitter);
                    gtk_label_set_text((GtkLabel*) m->downloading_label,
                                       ("Downloading: " + item->first.name).c_str());
                    
                    gtk_image_set_from_pixbuf((GtkImage*) m->thumbnail, item->second);
                    gtk_list_store_remove(GTK_LIST_STORE(a), &iter);
                    break;
                }
            } while (gtk_tree_model_iter_next(a, &iter));
            if (!y) {
                gtk_label_set_text((GtkLabel*) m->downloading_label, "Downloads Complete.");
                m->status_ii = "";
                m->download_progress = 1.0;
                gtk_image_set_from_icon_name((GtkImage*) m->thumbnail, "media-optical",
                                             GTK_ICON_SIZE_DIALOG);
            }
        }
    } else if (m->downloader.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        int a = m->downloader.get();
        m->downloaded_ids.push_back(a);
        auto item = std::find_if(m->items.begin(), m->items.end(),
                                 [&](std::pair<libbf::download, GdkPixbuf*> i) {
                                     return i.first.image_number == a;
                                 });
        if (item != m->items.end())
            m->add_to_view(*item);
        m->download_progress = 0.0;
    }

    return 1;
}