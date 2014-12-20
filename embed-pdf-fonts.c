/** embed-pdf-fonts.c
 *
 * Embed fonts into a PDF file using Poppler and Cairo.  This is done by not
 * saved the document directly via Poppler but rendered with Cairo.  This
 * procedure also respects the fontconfig settings such as substitution fonts,
 * so fonts not embedded but referenced will be replaced by their fontconfig
 * substitues after processing.
 *
 *
 * This file is based on the pdftops example from the Cairo documentation at
 * http://cairographics.org/renderpdf/
 *
 * Copyright 2014 Michael Fiedler <dev@michael-fiedler.net>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include <cairo.h>
#include <cairo-pdf.h>
#include <poppler.h>


int main(int argc, char *argv[]) {
    GError *error = NULL;

    if (argc != 3) {
        printf("Usage: %s input.pdf output.pdf\n", argv[0]);
        return 2;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];
    g_type_init();


    gchar *input_absolute = NULL;
    if (g_path_is_absolute(input_filename)) {
        input_absolute = g_strdup(input_filename);
    } else {
        gchar *dir = g_get_current_dir();
        input_absolute = g_build_filename(dir, input_filename, NULL);
        g_free(dir);
    }

    gchar *input_uri = g_filename_to_uri(input_absolute, NULL, &error);
    g_free(input_absolute);
    if (input_uri == NULL) {
        printf("poppler fail: %s\n", error->message);
        return EXIT_FAILURE;
    }

    PopplerDocument *document = poppler_document_new_from_file(input_uri, NULL, &error);
    if (document == NULL) {
        printf("poppler fail: %s\n", error->message);
        return EXIT_FAILURE;
    }

    int num_pages = poppler_document_get_n_pages(document);

    double _ = 42; // dummy value, size will be changed for each page
    cairo_surface_t *surface = cairo_pdf_surface_create(output_filename, _, _);
    cairo_t *cr = cairo_create(surface);

    for (int i = 0; i < num_pages; i++) {
        PopplerPage *page = poppler_document_get_page(document, i);
        if (page == NULL) {
            printf("poppler fail: page not found\n");
            return EXIT_FAILURE;
        }

        double width, height;
        poppler_page_get_size(page, &width, &height);
        cairo_pdf_surface_set_size(surface, width, height);
        cairo_save(cr);
        poppler_page_render_for_printing(page, cr);
        cairo_restore(cr);
        cairo_surface_show_page(surface);

        g_object_unref(page);
    }

    cairo_status_t status = cairo_status(cr);
    if (status)
        printf("%s\n", cairo_status_to_string(status));
    cairo_destroy(cr);

    cairo_surface_finish(surface);

    status = cairo_surface_status(surface);
    if (status)
        printf("%s\n", cairo_status_to_string(status));
    cairo_surface_destroy(surface);

    g_object_unref(document);
}
