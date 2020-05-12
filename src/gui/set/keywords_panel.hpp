//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <gui/set/panel.hpp>
#include <gui/control/filter_ctrl.hpp>

class wxSplitterWindow;
class KeywordList;
class TextCtrl;
struct KeywordSelectEvent;
class FilterCtrl;

// ----------------------------------------------------------------------------- : KeywordsPanel

/// A panel for listing and editing the keywords in a set
class KeywordsPanel : public SetWindowPanel {
public:
  KeywordsPanel(Window* parent, int id);
  ~KeywordsPanel();
  
  virtual void onChangeSet();
  virtual void onAction(const Action&, bool);
  
  // --------------------------------------------------- : UI
  
  virtual void initUI   (wxToolBar* tb, wxMenuBar* mb);
  virtual void destroyUI(wxToolBar* tb, wxMenuBar* mb);
  virtual void onUpdateUI(wxUpdateUIEvent&);
  virtual void onCommand(int id);
  
  // --------------------------------------------------- : Clipboard
  virtual bool canCut() const;
  virtual bool canCopy() const;
  virtual bool canPaste() const;
  virtual void doCut();
  virtual void doCopy();
  virtual void doPaste();

  virtual bool canSelectAll() const;
  virtual void doSelectAll();

private:
  DECLARE_EVENT_TABLE();
  
  /// Find the code to insert based on the ref_scripts for the parameters of the current keyword
  String runRefScript(int i);
  
  /// Actual intialization of the controls
  void initControls();
  
  // --------------------------------------------------- : Controls
  wxSplitterWindow* splitter;
  wxPanel*          panel;
  wxSizer*          sp;
  KeywordList*      list;
  TextCtrl*         keyword;
  TextCtrl*         match;
  TextCtrl*         reminder;
  TextCtrl*         rules;
  wxMenu*           menuKeyword;
  wxStaticText*     fixedL;
  wxSizer*          fixed;
  wxStaticText*     errors;
  wxChoice*         mode;
  wxButton*         add_param;
  wxButton*         ref_param;
  FilterCtrl*       filter;
  String            filter_value;
  
  // --------------------------------------------------- : Events
  void onKeywordSelect(KeywordSelectEvent& ev);
  void onModeChange(wxCommandEvent& ev);
};

