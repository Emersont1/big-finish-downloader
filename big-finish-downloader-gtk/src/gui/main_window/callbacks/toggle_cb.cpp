#include <libbf/gui/modules/main_window.hpp>

void libbf::gui::main_window::toggle_cb(GtkCellRendererToggle * cell,
                                        char * path, void * d) {
  auto        m = (libbf::gui::main_window *) d;
  GtkTreeIter iter;
  auto        a = gtk_tree_view_get_model(m->view_downloading);
  gtk_tree_model_get_iter_from_string(a, &iter, path);
  GValue x;
  g_value_init(&x, G_TYPE_BOOLEAN);
  g_value_set_boolean(&x, !gtk_cell_renderer_toggle_get_active(cell));
  gtk_list_store_set_value(m->list_downloading, &iter, 1, &x);
}