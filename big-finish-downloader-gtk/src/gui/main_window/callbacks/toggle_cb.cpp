#include <fstream>
#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::toggle_cb(GtkCellRendererToggle * cell,
                                        char * path, void * d) {
  auto        m = (libbf::gui::main_window *) d;
  GtkTreeIter iter;
  auto        a = gtk_tree_view_get_model(m->view_downloading);
  gtk_tree_model_get_iter_from_string(a, &iter, path);
  GValue x = G_VALUE_INIT;
  g_value_init(&x, G_TYPE_BOOLEAN);
  bool y = gtk_cell_renderer_toggle_get_active(cell);
  g_value_set_boolean(&x, !y);

  int id;
  gtk_tree_model_get(a, &iter, 3, &id, -1);

  m->shoud_download[std::to_string(id)] = y;
  gtk_list_store_set_value(m->list_downloading, &iter, 1, &x);
  g_value_unset(&x);
}