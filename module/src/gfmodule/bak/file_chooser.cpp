//

#include <stdio.h>
#include <string>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Icon.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNM_Image.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Double_Window.H>
#include <string.h>
#include "myassert.h"
#include "geoshape.h"
#include "GFimg.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#define username_str ("zgjkyfzx")
#define passwd_str ("zgjkyfzx")
using namespace boost::filesystem;
//std::vector<std::string> vector_files;

static std::string tiff_filename;
static std::string xml_filename;
static std::string rpb_filename ;
static std::string save_dir;
static std::string save_filename;
static std::string username;
static std::string password;

static int isContinue = 0;// 1 represent processing
//static int local_status = 1;

Fl_Input		*tifffile;
Fl_Input		*xmlfile;
Fl_Input		*rpbfile;
Fl_Input		*savefile;
Fl_Input		*resfile;
Fl_Input        *username_input;
Fl_Input        *password_input;
Fl_Box          *introtxt;
Fl_Button       * enterbtn;
Fl_Button       * cancelbtn;
//Fl_File_Browser		*files;
Fl_File_Chooser		*tifffc;
Fl_File_Chooser		*xmlfc;
Fl_File_Chooser		*rpbfc;
Fl_File_Chooser		*savefc;
Fl_Window          * login ;
Fl_Double_Window	*window;// Main window
//Fl_Shared_Image		*image = 0;



void        processing();
void        screenTomain();
void		close_callback(void);
void		create_callback(void);
void		fc_callback(Fl_File_Chooser *, void *);
void		tiffshow_callback(void);
void		xmlshow_callback(void);
void		rpbshow_callback(void);
void		saveshow_callback(void);
void        begin_callback(void);
void        stop_callback(void);
void        username_callback(void);
void        password_callback(void);
void        enter_callback(void);
void        cancel_callback(void);
void processing()
{
    if (isContinue == 1)
    {
        if(tiff_filename.empty())
        {
            fl_message("please select the \".tiff\" file");
            isContinue = 0;
            return;
        }       
        if(xml_filename.empty())
        {
            fl_message("please select the \".xml\" file");
            isContinue = 0;
            return;
        }       
        if(rpb_filename.empty())
        {
            fl_message("please select the \".rpb\" file");
            isContinue = 0;
            return;
        }       
        if(save_dir.empty())
        {
            fl_message("please select the output directory");
            isContinue = 0;
            return;
        }       
        save_filename=resfile->value();  
        if(save_filename.empty())
        {
            fl_message("please input the result name");
            isContinue = 0;
            return;
        }  
        if(tiff_filename.find(".tiff")==std::string::npos)
        {
            fl_message("please input the correct tiff file");
            isContinue = 0;
            return;
        }     
        if(xml_filename.find(".xml")==std::string::npos)
        {
            fl_message("please input the correct xml file");
            isContinue = 0;
            return;
        }     
        if(rpb_filename.find(".rpb")==std::string::npos)
        {
            fl_message("please input the correct rpb file");
            isContinue = 0;
            return;
        }     
        if(!is_directory(save_dir))
        {
            fl_message("please select the correct output directory");
            isContinue = 0;
            return;
        } 
        std::string savepath = save_dir+save_filename;
        printf("tiff_filename:%s\n",tiff_filename.c_str());
        printf("xml_filename:%s\n",xml_filename.c_str());
        printf("rpb_filename:%s\n",rpb_filename.c_str());
        printf("savepath:%s\n",savepath.c_str());
    GFimg * gf = new GFimg(tiff_filename, 0, xml_filename,rpb_filename);
 gf->getCorner();
    gf->init();
    gf->caldensity();
    gf->writeDen(savepath);
    delete gf; gf=NULL;
    }
}

void username_callback(Fl_Widget * cb) 
{
    assert(true==false);
}

void password_callback(Fl_Widget * cb)
{
    assert(true == false);
}

void enter_callback(Fl_Widget * cb)
{
    printf("enter_callback\n");
    std::string uin = username_input->value();
    std::string pin = password_input->value();
    if((uin.compare(username_str)== 0) && (pin.compare(passwd_str)== 0))
    {
        printf("login sucess\n");
        if(NULL!=login){
            login->hide();
        }
        screenTomain();
    }
}

void cancel_callback(Fl_Widget * cb)
{
    assert(true == false);
}


int			// O - Exit status
main(int  argc,		// I - Number of command-line arguments
     char *argv[])	// I - Command-line arguments
{
        
     login = new Fl_Window(450,200);
    introtxt  = new Fl_Box(FL_FRAME_BOX, 0,0, 450,70,
            " Welcome to the GaoFen Schistosomiasis risk estimation system!"
            );
    int y = 70;
    username_input = new Fl_Input(100,y, 250,30, "username:");y+=35;
    password_input = new Fl_Input(100,y, 250,30, "password:");y+=35;
    enterbtn = new Fl_Button(100,y, 155, 30,"login");
    enterbtn->callback(enter_callback);
    cancelbtn = new Fl_Button(355,y, 55, 30, "cancel");
    login->resizable();
    login->end();
    login->show();
    Fl::run();
    return (0);
}
void screenTomain()
{
        Fl_Button		*tiffbutton;// Buttons
        Fl_Button		*xmlbutton;// Buttons
        Fl_Button		*rpbbutton;// Buttons
        Fl_Button		*savebutton;// Buttons
        Fl_Button		*beginbutton;// Buttons
        Fl_Button		*stopbutton;// Buttons
        Fl_File_Icon		*icon;	// New file icon
  

  

  // Make the file chooser...
  Fl::scheme(NULL);
  Fl_File_Icon::load_system_icons();

  tifffc = new Fl_File_Chooser(NULL, "*.tiff", Fl_File_Chooser::SINGLE, "Choose the \".tiff\" file");
  tifffc->callback(fc_callback);

  xmlfc = new Fl_File_Chooser(NULL, "*.xml", Fl_File_Chooser::SINGLE, "Choose the \".xml\" file");
  xmlfc->callback(fc_callback);

  rpbfc = new Fl_File_Chooser(NULL, "*.rpb", Fl_File_Chooser::SINGLE, "Choose the \".rpb\" file");
  rpbfc->callback(fc_callback);
 
  savefc = new Fl_File_Chooser(NULL, "*", Fl_File_Chooser::DIRECTORY, "Choose the directory for output");
  rpbfc->callback(fc_callback);
 // Register the PS and PDF image types...
 // Fl_Shared_Image::add_handler(pdf_check);
 // Fl_Shared_Image::add_handler(ps_check);

  // Make the main window...
  window = new Fl_Double_Window(405, 215, "Select GaoFen images");

  tifffile = new Fl_Input(50, 10, 315, 25, "tiff:");
  xmlfile = new Fl_Input(50, 50, 315, 25, "xml:");
  rpbfile = new Fl_Input(50, 90, 315, 25, "rpb:");
  savefile = new Fl_Input(50, 130, 315, 25, "save:");
  resfile = new Fl_Input(140, 170, 150, 25, "input result name:");

  tifffile->value(NULL);
  xmlfile->value(NULL);
  rpbfile->value(NULL);
  savefile->value(NULL);
  resfile->value(NULL);
  tiffbutton = new Fl_Button(365, 10, 25, 25,"...");
  tiffbutton->labelcolor(FL_YELLOW);
  tiffbutton->callback((Fl_Callback *)tiffshow_callback);

  xmlbutton = new Fl_Button(365, 50, 25, 25,"...");
  xmlbutton->labelcolor(FL_YELLOW);
  xmlbutton->callback((Fl_Callback *)xmlshow_callback);

  rpbbutton = new Fl_Button(365, 90, 25, 25,"...");
  rpbbutton->labelcolor(FL_YELLOW);
  rpbbutton->callback((Fl_Callback *)rpbshow_callback);

  savebutton = new Fl_Button(365, 130, 25, 25,"...");
  savebutton->labelcolor(FL_YELLOW);
  savebutton->callback((Fl_Callback *)saveshow_callback);
  
  beginbutton = new Fl_Button(300, 170, 45, 25,"start");
  beginbutton->labelcolor(FL_GREEN);
  beginbutton->callback((Fl_Callback *)begin_callback);
  
  stopbutton = new Fl_Button(355, 170, 45, 25,"stop");
  stopbutton->labelcolor(FL_RED);
  stopbutton->callback((Fl_Callback *)stop_callback);
  window->resizable();
  window->end();
  window->show();
  Fl::run();
}


void
close_callback(void)
{
  exit(0);
}



void
fc_callback(Fl_File_Chooser *fc,	// I - File chooser
            void            *data)	// I - Data
{
  const char		*filename;	// Current filename


  printf("fc_callback(fc = %p, data = %p)\n", fc, data);

  filename = fc->value();

  printf("    filename = \"%s\"\n", filename ? filename : "(null)");
}





Fl_Image *			// O - Page image or NULL
pdf_check(const char *name,	// I - Name of file
          uchar      *header,	// I - Header data
	  int)			// I - Length of header data (unused)
{
  const char	*home;		// Home directory
  char		preview[FL_PATH_MAX],	// Preview filename
		command[FL_PATH_MAX];	// Command


  if (memcmp(header, "%PDF", 4) != 0)
    return 0;

  home = getenv("HOME");
  sprintf(preview, "%s/.preview.ppm", home ? home : "");

  sprintf(command,
          "gs -r100 -dFIXED -sDEVICE=ppmraw -dQUIET -dNOPAUSE -dBATCH "
	  "-sstdout=\"%%stderr\" -sOUTPUTFILE=\'%s\' "
	  "-dFirstPage=1 -dLastPage=1 \'%s\' 2>/dev/null", preview, name);

  if (system(command)) return 0;

  return new Fl_PNM_Image(preview);
}


//
// 'ps_check()' - Check for and load the first page of a PostScript file.
//

Fl_Image *			// O - Page image or NULL
ps_check(const char *name,	// I - Name of file
         uchar      *header,	// I - Header data
	 int)			// I - Length of header data (unused)
{
  const char	*home;		// Home directory
  char		preview[FL_PATH_MAX],	// Preview filename
		outname[FL_PATH_MAX],	// Preview PS file
		command[FL_PATH_MAX];	// Command
  FILE		*in,		// Input file
		*out;		// Output file
  int		page;		// Current page
  char		line[256];	// Line from file


  if (memcmp(header, "%!", 2) != 0)
    return 0;

  home = getenv("HOME");
  sprintf(preview, "%s/.preview.ppm", home ? home : "");

  if (memcmp(header, "%!PS", 4) == 0) {
    // PS file has DSC comments; extract the first page...
    sprintf(outname, "%s/.preview.ps", home ? home : "");

    if (strcmp(name, outname) != 0) {
      in   = fl_fopen(name, "rb");
      out  = fl_fopen(outname, "wb");
      page = 0;

      while (fgets(line, sizeof(line), in) != NULL) {
	if (strncmp(line, "%%Page:", 7) == 0) {
          page ++;
	  if (page > 1) break;
	}

	fputs(line, out);
      }

      fclose(in);
      fclose(out);
    }
  } else {
    // PS file doesn't have DSC comments; do the whole file...
    strncpy(outname, name, sizeof(outname) - 1);
    outname[sizeof(outname) - 1] = '\0';
  }

  sprintf(command,
          "gs -r100 -dFIXED -sDEVICE=ppmraw -dQUIET -dNOPAUSE -dBATCH "
	  "-sstdout=\"%%stderr\" -sOUTPUTFILE=\'%s\' \'%s\' 2>/dev/null",
	  preview, outname);

  if (system(command)) return 0;

  return new Fl_PNM_Image(preview);
}


//
// 'show_callback()' - Show the file chooser...
//

void tiffshow_callback(void)
{
  int	i;			// Looping var
  int	count;			// Number of files selected
  char	relative[FL_PATH_MAX];	// Relative filename


//  if (filter->value()[0])
//    fc->filter(filter->value());

  tifffc->show();

  while (tifffc->visible()) {
    Fl::wait();
  }

  count = tifffc->count();
  if (count > 0)
  {
  //  tifffile->clear();

    for (i = 1; i <= count; i ++)
    {
      if (!tifffc->value(i))
        break;
      //  printf("value:%s\n",tifffc->value(i));
      tifffile->value(tifffc->value(i));
       tiff_filename = std::string(tifffc->value(i));
    }
    tifffile->redraw();
   // files->redraw();
  }
}

void xmlshow_callback(void)
{
  int	i;			// Looping var
  int	count;			// Number of files selected
  char	relative[FL_PATH_MAX];	// Relative filename



  xmlfc->show();

  while (xmlfc->visible()) {
    Fl::wait();
  }

  count = xmlfc->count();
  if (count > 0)
  {
   // files->clear();

    for (i = 1; i <= count; i ++)
    {
      if (!xmlfc->value(i))
        break;
        xmlfile->value(xmlfc->value(i));
       xml_filename = std::string(xmlfc->value(i));
    }
 //   xmlfile->redraw();
  //  files->redraw();
  }
}


void rpbshow_callback(void)
{
  int	i;			// Looping var
  int	count;			// Number of files selected
  char	relative[FL_PATH_MAX];	// Relative filename


//  if (filter->value()[0])
//    fc->filter(filter->value());

  rpbfc->show();

  while (rpbfc->visible()) {
    Fl::wait();
  }

  count = rpbfc->count();
  if (count > 0)
  {
 //   files->clear();

    for (i = 1; i <= count; i ++)
    {
      if (!rpbfc->value(i))
        break;
       rpbfile->value(rpbfc->value(i));
       rpb_filename = std::string(rpbfc->value(i));

    }
    rpbfile->redraw();
  //  files->redraw();
  }
}


void saveshow_callback(void)
{
  int	i;			// Looping var
  int	count;			// Number of files selected
  char	relative[FL_PATH_MAX];	// Relative filename



  savefc->show();

  while (savefc->visible()) {
    Fl::wait();
  }

  count = savefc->count();
  if (count > 0)
  {
  //  files->clear();

    for (i = 1; i <= count; i ++)
    {
      if (!savefc->value(i))
        break;
       savefile->value(savefc->value(i));
    save_dir = std::string(savefc->value(i));

    }
    savefile->redraw();
  }
}

void begin_callback(void)
{
   // fl_message("begin to processing");
    if(isContinue ==0)
    {
        isContinue = fl_choice("Are you sure to begin process?","NO","YES",0L);
        processing();       
    }else
    {
        fl_message("Data is under processing");
    }
        printf("isContinue:%d\n",isContinue);
   //  assert(true == false);
}
void stop_callback(void)
{
   // fl_message("begin to processing");
   if(isContinue !=0)
   {
    isContinue = fl_choice("Are you sure to cancle process?","NO","YES",0L);
   }else
   {
    fl_message("processing is not started");
   }
    printf("isContinue:%d\n",isContinue);
   //  assert(true == false);
}
