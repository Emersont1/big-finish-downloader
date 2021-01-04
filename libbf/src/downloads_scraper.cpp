#include <iostream>

#include <cpr/cpr.h>
#include <lexbor/dom/interfaces/element.h>
#include <lexbor/html/html.h>
#include <lexbor/html/interfaces/link_element.h>
#include <lexbor/html/parser.h>

#include <libbf/downloads.hpp>
#include <libbf/exceptions.hpp>

libbf::download create_download(lxb_dom_element_t*);

std::vector<libbf::download> libbf::download::get_downloads(libbf::login_cookie& cookie) {
    std::string url = "/customers/my_account/";
    std::vector<libbf::download> elems;
    while (true) {
        cpr::Response r = cpr::Get(cpr::Url{"https://www.bigfinish.com" + url},
                                   cpr::Cookies{{"CakeCookie[Customer]", cookie.get_customer()},
                                                {"CAKEPHP", cookie.get_cakephp()}});

        lxb_status_t status;

        lxb_html_document_t* document = lxb_html_document_create();
        status = lxb_html_document_parse(document, (const lxb_char_t*) r.text.c_str(),
                                         r.text.size());

        if (status != LXB_STATUS_OK) {
            throw libbf::parse_failed_exception();
        }

        // currently the page shows 50 products per page
        lxb_dom_collection_t* collection = lxb_dom_collection_make(&document->dom_document, 50);

        status = lxb_dom_elements_by_class_name(lxb_dom_interface_element(document->body),
                                                collection,
                                                (const lxb_char_t*) "account-release-download", 24);

        for (size_t i = 0; i < lxb_dom_collection_length(collection); i++) {
            lxb_dom_element_t* element = lxb_dom_collection_element(collection, i);
            elems.push_back(create_download(element));
        }

        lxb_dom_collection_destroy(collection, true);

        // Next Page
        {
            lxb_dom_collection_t* nextPage = lxb_dom_collection_make(&document->dom_document, 1);

            lxb_dom_elements_by_class_name(lxb_dom_interface_element(document->body), nextPage,
                                           (const lxb_char_t*) "page_nav", 8);

            if (lxb_dom_collection_length(nextPage) > 0) {
                lxb_dom_element_t* el = lxb_dom_collection_element(nextPage, 0);
                size_t len = 0;
                std::string u((char*) lxb_dom_element_get_attribute(
                        (lxb_dom_element_t*) el->node.first_child, (const lxb_char_t*) "href", 4,
                        &len));
                url = u;
                lxb_dom_collection_destroy(nextPage, true);
                lxb_html_document_destroy(document);
            } else {
                lxb_dom_collection_destroy(nextPage, true);
                lxb_html_document_destroy(document);
                return elems;
            }
        }
    }
}