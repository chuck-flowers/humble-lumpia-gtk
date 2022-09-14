#include <gtk/gtk.h>
#include <stdio.h>

#include "fs_utils.h"
#include "hl_utils.h"
#include "logging.h"
#include "string_list.h"

void on_activate();
void on_refresh_button_clicked();
void on_sync_button_clicked();

int main(int argc, char **argv) {
	LOG_TRACE("main");

	initialize_fs_utils();

	// Define application
	LOG_TRACE("main: creating app");
	GtkApplication *app = gtk_application_new("dev.chuck-flowers.humble-lumpia-gtk", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK (on_activate), NULL);

	// Run the application
	LOG_TRACE("main: running app");
	const int status = g_application_run(G_APPLICATION(app), argc, argv);

	// Cleanup and report status
	LOG_TRACE("main: cleaning up app");
	g_object_unref(app);
	return status;
}

void on_activate(GtkApplication *app) {
	LOG_TRACE("activate");

	const char *main_ui_file = get_installed_file("/share/humble-lumpia-gtk/ui/main.ui");
	if (main_ui_file == NULL) {
		fprintf(stderr, "Failed to find the main UI file\n");
		return;
	}

	// Build the UI
	LOG_TRACE("activate: building UI");
	GtkBuilder *builder = gtk_builder_new_from_file(main_ui_file);

	// Window
	LOG_TRACE("activate: extracting UI elements");
	GObject *root_window = gtk_builder_get_object(builder, "root_window");
	gtk_application_add_window(app, GTK_WINDOW(root_window));

	// Refresh button
	GObject *refresh_button = gtk_builder_get_object(builder, "refresh_button");
	g_signal_connect(refresh_button, "clicked", G_CALLBACK(on_refresh_button_clicked), NULL);

	// Sync button
	GObject *sync_button = gtk_builder_get_object(builder, "sync_button");
	g_signal_connect(sync_button, "clicked", G_CALLBACK(on_sync_button_clicked), NULL);

	LOG_TRACE("activate: showing window");
	gtk_window_present(GTK_WINDOW(root_window));
}

void on_refresh_button_clicked() {
	LOG_TRACE("on_refresh_button_clicked");

	const StringList *available_versions = hl_get_available_versions();
	const StringList *installed_versions = hl_get_installed_versions();

	for (int i = 0; i < available_versions->length; i++) {
		fprintf(stdout, "\t%s\n", available_versions->elements[i]);
	}

	for (int i = 0; i < installed_versions->length; i++) {
		fprintf(stdout, "%s\n", available_versions->elements[i]);
	}
}

void on_sync_button_clicked() {
	LOG_TRACE("on_sync_button_clicked");
}

