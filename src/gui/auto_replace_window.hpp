//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <data/word_list.hpp>

class AutoReplaceList;

// ----------------------------------------------------------------------------- : AutoReplaceWindow

/// A window for editing the AutoReplace words
class AutoReplaceWindow : public wxDialog {
public:
  /// Edit auto replace words for the given game
  AutoReplaceWindow(Window* parent, const Game& game);
  
private:
  DECLARE_EVENT_TABLE();
  
  AutoReplaceList* list;
  wxStaticText* matchL, *replaceL;
  wxTextCtrl* match, *replace;
  wxCheckBox* enabled, *whole_word;
  wxCheckBox* use_auto_replace;
  wxButton* add, *remove;
  
  bool in_event; ///< No recursion between event handlers
  
  void onItemSelect(wxCommandEvent&);
  void onItemChange(wxCommandEvent&);
  
  void onEnable(wxCommandEvent&);
  void onAdd(wxCommandEvent&);
  void onRemove(wxCommandEvent&);
  void onDefault(wxCommandEvent&);
  void onOk(wxCommandEvent&);
  
  void enable();
  void refreshItem();
  void updateItem();
  void store();
};

