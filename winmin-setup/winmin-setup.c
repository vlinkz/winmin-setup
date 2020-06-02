#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <ctype.h>
#include <stdio.h>
//#include <libvirt/libvirt-common.h>
//#include <libvirt/libvirt-domain.h>
#include <Python.h>
#define PY_SSIZE_T_CLEAN
#include <spice-client-gtk-3.0/spice-client-gtk.h>


SpiceSession * session;
SpiceChannel * mainchannel;
SpiceDisplay * display;
GtkWidget * displaywidget;
GtkWidget	*window;
GtkWidget	*btn_next;
GtkWidget	*btn_close;
GtkWidget	*label1;
GtkWidget   *installeriso;
GtkWidget   *stack;
GtkWidget   *mainbox;
GtkWidget   *bootloading;
GtkWidget   *instructionstack;
GtkWidget   *nextinstruction;
GtkWidget   *previousinstruction;
GtkWidget   *finalscreen;
GtkWidget   *btn_done;
GtkBuilder	*builder;
char** sock;
char** isopath;
int instructionindex;

void get_socket()
{
    /*wchar_t *program = Py_DecodeLocale("winsetup.py", NULL);
    Py_SetProgramName(program);
    Py_Initialize();
    PyRun_SimpleFile("pywinminsetup.py\n");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    
    PyMem_RawFree(program);
    return 0;*/
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;
    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("pywinminsetup");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    /* Error checking of pName left out */
    pFunc = PyObject_GetAttrString(pModule, "call");

    pArgs = PyTuple_New(1);
    pValue = PyUnicode_FromString(isopath);

    if (!pValue) {
        Py_DECREF(pArgs);
        Py_DECREF(pModule);
        printf("Cannot convert argument\n");
        return 1;
    }
    PyTuple_SetItem(pArgs,0,pValue);
    //PyObject_SetItem(pArgs,0,isopath);*/
    while (gtk_events_pending ())
        gtk_main_iteration ();
    pValue = PyObject_CallObject(pFunc, pArgs);

    Py_DECREF(pArgs);
    if (pValue != NULL) {
        printf("Result of call: %s\n", PyUnicode_AsUTF8(pValue));
        sock = PyUnicode_AsUTF8(pValue);
        Py_DECREF(pValue);
    }
    else {
        printf("NULL\n");
        exit(120);
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    setup_spice(0);
    return 0;
}

void get_socket_noargs(char** funct)
{

    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;
    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("pywinminsetup");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    pFunc = PyObject_GetAttrString(pModule, funct); //boot


    pValue = PyObject_CallObject(pFunc, NULL);

    //Py_DECREF(pArgs);
    if (pValue != NULL) {
        printf("Result of call: %s\n", PyUnicode_AsUTF8(pValue));
        sock = PyUnicode_AsUTF8(pValue);
        Py_DECREF(pValue);
    }
    else {
        printf("NULL\n");
        exit(120);
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    setup_spice(1);
    return 0;
}

void setup_spice(int count) {

  session = spice_session_new();

  g_object_set(session,"uri",sock);
  
  //char** test;
  //g_object_get(session,"uri",&test);
  //printf("URI: %s\n",test);

  mainchannel =  spice_channel_new(session,1,0);
  spice_session_connect(session);

  if (count == 0) {
      gtk_widget_destroy(bootloading);
      printf("Destroy bootloader\n");
  }
  if (count == 1) {
      gtk_widget_destroy(displaywidget);
  }

  display = spice_display_new(session,0);
  displaywidget = GTK_WIDGET(display);
  //GtkPaned * mainboxpane = GTK_PANED(mainbox);
  gtk_window_resize(window, 1318, 800);
  gtk_window_set_position(window, GTK_WIN_POS_CENTER);

  gtk_paned_add2(mainbox, displaywidget);

}

int main(int argc, char *argv[]) {

    /*if( ! g_thread_supported() )
        g_thread_init( NULL );

    gdk_threads_init();
    gdk_threads_enter();*/
	gtk_init(&argc, &argv); // init Gtk

	builder = gtk_builder_new_from_file ("winmin.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "WinminSetupIntro"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	btn_next = GTK_WIDGET(gtk_builder_get_object(builder, "first_next"));
	btn_close = GTK_WIDGET(gtk_builder_get_object(builder, "close"));
	installeriso = GTK_WIDGET(gtk_builder_get_object(builder, "installeriso"));
    stack = GTK_WIDGET(gtk_builder_get_object(builder,"stack"));
    mainbox = GTK_WIDGET(gtk_builder_get_object(builder,"mainbox"));
    bootloading = GTK_WIDGET(gtk_builder_get_object(builder,"bootloading"));
    instructionstack = GTK_WIDGET(gtk_builder_get_object(builder,"instructionstack"));
    nextinstruction = GTK_WIDGET(gtk_builder_get_object(builder,"nextinstruction"));
    previousinstruction = GTK_WIDGET(gtk_builder_get_object(builder,"previousinstruction"));
    finalscreen = GTK_WIDGET(gtk_builder_get_object(builder,"finalscreen"));
    btn_done = GTK_WIDGET(gtk_builder_get_object(builder,"done"));



	gtk_widget_show(window);

	gtk_main();

	return EXIT_SUCCESS;
	}

void on_close_clicked (GtkButton *b) {
    exit(1);
}

void on_installeriso_file_set (GtkFileChooserButton * f) {
    gtk_widget_unset_state_flags(btn_next, GTK_STATE_FLAG_INSENSITIVE);
    isopath = gtk_file_chooser_get_filename(installeriso);
    printf("ISOPATH: %s\n",isopath);
}

void on_first_next_clicked (GtkButton *b) {
    gtk_stack_set_visible_child(stack, mainbox);
    while (gtk_events_pending ())
        gtk_main_iteration ();
    gtk_widget_hide(btn_close);
    gtk_widget_hide(btn_next);
    instructionindex = 1;

    get_socket();
}

void on_nextinstruction_clicked() {
    if (instructionindex < 9) {
        instructionindex += 1;
        char step[10];
        sprintf(step,"step%d",instructionindex);
        printf("%s\n",step);
        gtk_stack_set_visible_child(instructionstack,GTK_WIDGET(gtk_builder_get_object(builder,step)));
        gtk_widget_unset_state_flags(previousinstruction, GTK_STATE_FLAG_INSENSITIVE);
        if (instructionindex >= 9) {
            gtk_widget_set_state_flags(nextinstruction,GTK_STATE_FLAG_INSENSITIVE,TRUE);
        } 
    }
}

void on_previousinstruction_clicked() {
    if (instructionindex > 1) {
        instructionindex -= 1;
        char step[10];
        sprintf(step,"step%d",instructionindex);
        printf("%s\n",step);
        gtk_stack_set_visible_child(instructionstack,GTK_WIDGET(gtk_builder_get_object(builder,step)));
        gtk_widget_unset_state_flags(nextinstruction, GTK_STATE_FLAG_INSENSITIVE);
        if (instructionindex <= 1) {
            gtk_widget_set_state_flags(previousinstruction,GTK_STATE_FLAG_INSENSITIVE,TRUE);
        }
    }
}

void on_boot_clicked() {
    get_socket_noargs("boot");
}

void on_savebutton_clicked() {
    gtk_stack_set_visible_child(stack, finalscreen);
    gtk_widget_show(btn_done);
    get_socket_noargs("done");
}

void on_done_clicked() {
    exit(1);
}
