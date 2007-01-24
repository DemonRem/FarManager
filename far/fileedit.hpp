#ifndef __FILEEDITOR_HPP__
#define __FILEEDITOR_HPP__
/*
fileedit.hpp

�������������� ����� - ���������� ��� editor.cpp

*/

#include "frame.hpp"
#include "editor.hpp"
#include "keybar.hpp"

class NamesList;

/* $ 27.05.2001 DJ
   ���� �������� Editor::SaveFile()
*/
enum {
    SAVEFILE_ERROR   = 0,         // �������� ���������, �� ����������
    SAVEFILE_SUCCESS = 1,         // ���� ������� ���������, ���� ��������� ���� �� ����
    SAVEFILE_CANCEL  = 2          // ���������� ��������, �������� �� ���������
};
/* DJ $ */

enum FEOPMODEEXISTFILE{
  FEOPMODE_QUERY        =0,
  FEOPMODE_NEWIFOPEN    =1,
  FEOPMODE_USEEXISTING  =2,
  FEOPMODE_BREAKIFOPEN  =3,
};

enum FFILEEDIT_FLAGS{
  FFILEEDIT_NEW            = 0x00010000,  // ���� ���� ����������! ����� ��� ��� ������ �������! ���� ������ � ��� ���.
  FFILEEDIT_REDRAWTITLE    = 0x00020000,  // ����� ��������� ���������?
  FFILEEDIT_FULLSCREEN     = 0x00040000,  // ������������� �����?
  FFILEEDIT_DISABLEHISTORY = 0x00080000,  // ��������� ������ � �������?
  FFILEEDIT_ENABLEF6       = 0x00100000,  // ������������� �� ������ �����?
  FFILEEDIT_SAVETOSAVEAS   = 0x00200000,  // $ 17.08.2001 KM  ��������� ��� ������ �� AltF7.
                                          //   ��� �������������� ���������� ����� �� ������ ���
                                          //   ������� F2 ������� ����� ShiftF2.
  FFILEEDIT_ISNEWFILE      = 0x00400000,
  FFILEEDIT_SAVEWQUESTIONS = 0x00800000,  // ��������� ��� ��������
};


class FileEditor:public Frame
{
  private:
    typedef class Frame inherited;

    Editor *FEdit;
    KeyBar EditKeyBar;

    /* $ 07.05.2001 DJ */
    NamesList *EditNamesList;
    /* DJ $ */
    char FileName[NM*2];
    char FullFileName[NM*2];
    char StartDir[NM];
    char NewTitle[NM];

    char Title[512];
    char PluginTitle[512];
    char PluginData[NM*2];

    WIN32_FIND_DATA FileInfo;
    /* $ 13.02.2001 IS
         ���� �������� ����� ���������, ����� �� ��������� �� ����� ���
    */
    char AttrStr[4];
    /* IS $ */
    /* $ 12.02.2001 IS
         ���� �������� �������� ����� ��� ��������, ���������� ���-������...
    */
    DWORD FileAttributes;
    /* IS $ */
    /* $ 04.11.2003 SKV
      ���� �� ��������������� ��������� ��� save
    */
    BOOL  FileAttributesModified;
    /* SKV $ */
    DWORD SysErrorCode;

    //28.04.2005 AY: true ����� �������� ������������ (�.�. � �����������)
    bool bClosing;

    bool bEE_READ_Sent;

  public:
    FileEditor(const char *Name,int CreateNewFile,int EnableSwitch,
               int StartLine=-1,int StartChar=-1,int DisableHistory=FALSE,
               char *PluginData=NULL,int ToSaveAs=FALSE,
               int OpenModeExstFile=FEOPMODE_QUERY);
    /* $ 14.06.2002 IS
       DeleteOnClose ���� int:
         0 - �� ������� ������
         1 - ������� ���� � �������
         2 - ������� ������ ����
    */
    FileEditor(const char *Name,int CreateNewFile,int EnableSwitch,
               int StartLine,int StartChar,const char *Title,
               int X1,int Y1,int X2,int Y2, int DisableHistory,
               int DeleteOnClose=0,
               int OpenModeExstFile=FEOPMODE_QUERY);
    /* IS $ */
    /* $ 07.05.2001 DJ */
    virtual ~FileEditor();
    /* DJ $ */

  private:
    void DisplayObject();
    int  ProcessQuitKey(int FirstSave,BOOL NeedQuestion=TRUE);
    BOOL UpdateFileList();
    /* $ 10.10.2001 IS ��������� DeleteOnClose */
    /* $ 14.06.2002 IS
        DeleteOnClose ���� int:
          0 - �� ������� ������
          1 - ������� ���� � �������
          2 - ������� ������ ����
    */
    void SetDeleteOnClose(int NewMode);
    /* IS 14.06.2002 */
    /* IS 10.10.2001 */
    int ReProcessKey(int Key,int CalledFromControl=TRUE);

  public:
    /* $ 14.06.2002 IS
       DeleteOnClose ���� int:
         0 - �� ������� ������
         1 - ������� ���� � �������
         2 - ������� ������ ����
    */
    void Init(const char *Name,const char *Title,int CreateNewFile,int EnableSwitch,
              int StartLine,int StartChar,int DisableHistory,char *PluginData,
              int ToSaveAs, int DeleteOnClose,int OpenModeExstFile);
    /* IS $ */

    void InitKeyBar(void);                            // $ 07.08.2000 SVS - ������� ������������� KeyBar Labels
    int ProcessKey(int Key);
    int ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent);
    void ShowConsoleTitle();
    int IsFileChanged() {return(FEdit->IsFileChanged());};
    virtual int IsFileModified() {return(FEdit->IsFileModified());};

    void SetScreenPosition();                         // $ 28.06.2000 tran - NT Console resize - resize editor

    virtual int GetTypeAndName(char *Type,char *Name);
    virtual const char *GetTypeName(){return "[FileEdit]";};
    virtual int GetType() { return MODALTYPE_EDITOR; }


    virtual void OnDestroy();                         // $ 10.05.2001 DJ
    void SetNamesList (NamesList *Names);             // $ 07.05.2001 DJ

    int GetCanLoseFocus(int DynamicMode=FALSE);

    int FastHide();                                   // $ OT - ������� ��� ���� CtrlAltShift

    void SetEnableF6 (int AEnableF6) { Flags.Change(FFILEEDIT_ENABLEF6,AEnableF6); InitKeyBar(); }  // $ 10.05.2001 DJ
    /* $ 17.08.2001 KM
      ��������� ��� ������ �� AltF7. ��� �������������� ���������� ����� ��
      ������ ��� ������� F2 ������� ����� ShiftF2.
    */
    void SetSaveToSaveAs(int ToSaveAs) { Flags.Change(FFILEEDIT_SAVETOSAVEAS,ToSaveAs); InitKeyBar(); }
    /* KM $ */

    /* $ 08.12.2001 OT
      ���������� ������� ����, �������� �� ���� ���������
      ������������ ��� �������� ������� ���������� � ������� �� CtrlF10*/
    BOOL isTemporary();
    void ResizeConsole();
    void Show();

    int ReadFile(const char *Name,int &UserBreak);
    int SaveFile(const char *Name,int Ask,int TextFormat,int SaveAs);
    int EditorControl(int Command,void *Param);
    void SetPluginTitle(const char *PluginTitle);
    void SetTitle(const char *Title);
    virtual void GetTitle(char *Title,int LenTitle,int TruncSize=0);
    BOOL SetFileName(const char *NewFileName);
    int ProcessEditorInput(INPUT_RECORD *Rec);
    void SetLockEditor(BOOL LockMode);
    BOOL IsFullScreen(){return Flags.Check(FFILEEDIT_FULLSCREEN);}
    void ChangeEditKeyBar();
    void ShowStatus();

    DWORD GetFileAttributes(LPCTSTR);                 // $ 13.02.2001 IS - ������� ������ ����������� ������� �� win32 api

    void SetPluginData(char *PluginData);
    char *GetPluginData(void){return PluginData;};

    void GetEditorOptions(struct EditorOptions& EdOpt);
    void SetEditorOptions(struct EditorOptions& EdOpt);
};

#endif  // __FILEEDITOR_HPP__
