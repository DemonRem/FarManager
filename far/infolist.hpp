#ifndef __INFOLIST_HPP__
#define __INFOLIST_HPP__
/*
infolist.hpp

�������������� ������

*/

#include "panel.hpp"
#include "viewer.hpp"
//class Viewer;

/* $ 12.10.2001 SKV
  �������� Viewer ��� �� ����������� ������������� ������
  ������� DizView � �������� �� ������� ��� �� ����� ������.
*/
class DizViewer: public Viewer
{
public:
  int InRecursion;
  DizViewer():InRecursion(0){}
  int ProcessKey(int Key)
  {
    InRecursion=1;
    int res=Viewer::ProcessKey(Key);
    InRecursion=0;
    return res;
  }
  int ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent)
  {
    InRecursion=1;
    int res=Viewer::ProcessMouse(MouseEvent);
    InRecursion=0;
    return res;
  }
};
/* SKV$*/

class InfoList:public Panel
{
  private:
    DizViewer *DizView;
    int  PrevMacroMode;
    int  DizPresent;
    int  OldWrapMode;
    int  OldWrapType;
    char DizFileName[NM];

  private:
    void DisplayObject();
    void ShowDirDescription();
    void ShowPluginDescription();
    void PrintText(const char *Str);
    void PrintText(int MsgID);
    void PrintInfo(const char *Str);
    void PrintInfo(int MsgID);
    int  OpenDizFile(char *DizFile);
    void SetMacroMode(int Restore = FALSE);
    /* $ 30.04.2001 DJ */
    void DynamicUpdateKeyBar();
    /* DJ $ */

  public:
    InfoList();
    ~InfoList();

  public:
    int ProcessKey(int Key);
    int ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent);
    void Update(int Mode);
    virtual void SetFocus();
    virtual void GetTitle(char *Title,int LenTitle,int TruncSize=0);
    virtual void KillFocus();
    /* $ 30.04.2001 DJ */
    virtual BOOL UpdateKeyBar();
    virtual void CloseFile();
    /* DJ $ */
    /* $ 02.01.2002 IS
       �������� ��� ���������������� diz-�����
    */
    virtual int GetCurName(char *Name,char *ShortName);
    /* IS $ */
};

#endif  // __INFOLIST_HPP__
