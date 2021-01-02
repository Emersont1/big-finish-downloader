#include <iostream>

#include <lexbor/dom/interfaces/element.h>
#include <lexbor/dom/interfaces/text.h>
#include <lexbor/html/html.h>
#include <lexbor/html/interfaces/link_element.h>
#include <lexbor/html/parser.h>

#include <utils.hpp>

#include <libbf/downloads.hpp>
#include <libbf/exceptions.hpp>

libbf::download create_download(lxb_dom_element_t * e) {
  size_t len;
  auto   img_coll = lxb_dom_collection_make(e->node.owner_document, 1);
  lxb_dom_elements_by_tag_name(e, img_coll, (const lxb_char_t *) "img", 3);
  auto img = lxb_dom_collection_element(img_coll, 0);

  std::string img_src((char *) lxb_dom_element_get_attribute(
      img, (const lxb_char_t *) "src", 3, &len));
  std::string title((char *) lxb_dom_element_get_attribute(
      img, (const lxb_char_t *) "alt", 3, &len));

  // remove leading /image/release/
  auto num = std::stoi(img_src.substr(15, img_src.size() - 26));

  auto downloads = lxb_dom_collection_make(e->node.owner_document, 2);
  lxb_dom_elements_by_class_name(e, downloads,
                                 (const lxb_char_t *) "common-btn", 10);
  bool has_m4b = false;
  for (int i = 0; i < lxb_dom_collection_length(downloads); i++) {
    auto        elem = lxb_dom_collection_element(downloads, i);
    std::string type((char *) ((lxb_dom_text *) elem->node.first_child)
                         ->char_data.data.data);
    if (type.substr(0, 3) == "M4B") {
      has_m4b = true;
      break;
    }
  }

  std::vector<std::pair<std::string, int>> supp_downloads;
  auto sdownloads = lxb_dom_collection_make(e->node.owner_document, 10);
  lxb_dom_elements_by_tag_name(e, sdownloads, (const lxb_char_t *) "li", 2);
  for (int i = 0; i < lxb_dom_collection_length(sdownloads); i++) {
    auto        elem = lxb_dom_collection_element(sdownloads, i);
    auto        url = (lxb_dom_element *) elem->node.first_child->next;
    std::string name;
    if (url->node.first_child->next == nullptr)
      name = std::string((char *) ((lxb_dom_text *) url->node.first_child)
                             ->char_data.data.data);
    else {
      name = std::string(
          (char *) ((lxb_dom_text *) url->node.first_child->next->first_child)
              ->char_data.data.data);
    }
    std::string href((char *) lxb_dom_element_get_attribute(
        url, (const lxb_char_t *) "href", 4, &len));
    trim(name);

    supp_downloads.push_back(std::make_pair(name, std::stoi(href.substr(37))));
  }

  lxb_dom_collection_destroy(img_coll, true);
  lxb_dom_collection_destroy(downloads, true);

  return libbf::download(title, num, has_m4b, supp_downloads);
}
