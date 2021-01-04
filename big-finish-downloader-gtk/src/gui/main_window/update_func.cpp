#include <libbf/gui/modules/main_window.hpp>

#include <iostream>

int libbf::gui::main_window::update_func(void * d) {
  auto m = (libbf::gui::main_window *) d;

  gtk_progress_bar_set_fraction((GtkProgressBar *) m->progress_bar,
                                m->download_progress);
  gtk_label_set_text((GtkLabel*)m->downloading_status_ii, m->status_ii.c_str());

  if (!m->items_fut.valid() && m->items.size()==0) 
    m->items_fut = std::async(std::launch::async,&libbf::gui::main_window::get_items, m, m->cookie);
if(m->items_fut.valid()){
  if (m->items_fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    m->items = m->items_fut.get();
    for (auto x=  m->items.begin(); x !=  m->items.end(); ++x) {
      m->add_to_view(*x);
    }
  }}

  if(!m->downloader.valid())
{
   auto        a = gtk_tree_view_get_model(m->view_downloading);
   GtkTreeIter iter;
   if(gtk_tree_model_get_iter_first (a,
                                       &iter)){
   do{
     bool y;
      int id;
  gtk_tree_model_get(a, &iter, 1, &y,3, &id, -1);
  if(y){
      auto item = std::find_if(m->items.begin(), m->items.end(), [&](std::pair<libbf::download, GdkPixbuf *> i){return i.first.download_number==id;});
      if(item== m->items.end()){
        return 1;
      }

    m->downloader = std::async(std::launch::async,&libbf::gui::main_window::download, m, item->first);
    gtk_label_set_text((GtkLabel*)m->downloading_label, ("Downloading: "+item->first.name).c_str());

auto pixbuf = gdk_pixbuf_new_from_file(
          (m->cache + "img/" + std::to_string(item->first.download_number) + ".jpg").c_str(), nullptr);

gtk_image_set_from_pixbuf ((GtkImage *) m->thumbnail, pixbuf);    
g_object_unref(pixbuf);
 gtk_list_store_remove(GTK_LIST_STORE(a), &iter);
break;
  }
   }while(gtk_tree_model_iter_next(a, &iter));
}}
  else if (m->downloader.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
      int a = m->downloader.get();
      m->downloaded_ids.push_back(a);
      auto item = std::find_if(m->items.begin(), m->items.end(), [&](std::pair<libbf::download, GdkPixbuf *> i){return i.first.download_number==a;});
      if(item!= m->items.end())
      m->add_to_view(*item);
   
  }

  return 1;
}