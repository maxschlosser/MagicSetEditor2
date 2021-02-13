//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <gui/control/select_card_list.hpp>
#include <gui/util.hpp>
#include <data/card.hpp>
#include <wx/imaglist.h>

// ----------------------------------------------------------------------------- : SelectCardList

SelectCardList::SelectCardList(Window* parent, int id, long additional_style)
  : CardListBase(parent, id, additional_style)
{
  // create image list
  wxImageList* il = new wxImageList(15,15);
  il->Add(load_resource_image(_("sort_asc")),  Color(255,0,255));
  il->Add(load_resource_image(_("sort_desc")), Color(255,0,255));
  il->Add(load_resource_image(_("deselected")));
  il->Add(load_resource_image(_("selected")));
  AssignImageList(il, wxIMAGE_LIST_SMALL);
}
SelectCardList::~SelectCardList() {}

void SelectCardList::selectAll() {
  FOR_EACH_CONST(c, set->cards) {
    selected.insert(c);
  }
  Refresh(false);
}
void SelectCardList::selectNone() {
  selected.clear();
  Refresh(false);
}
bool SelectCardList::isSelected(const CardP& card) const {
  return selected.find(card) != selected.end();
}

void SelectCardList::getSelection(vector<CardP>& out) const {
  FOR_EACH_CONST(card, set->cards) {
    if (isSelected(card)) out.push_back(card);
  }
}

void SelectCardList::setSelection(const vector<CardP>& cards) {
  selected.clear();
  copy(cards.begin(), cards.end(), inserter(selected, selected.begin()));
}


void SelectCardList::onChangeSet() {
  CardListBase::onChangeSet();
  // init selected list: select all
  selected.clear();
  selectAll();
}

int SelectCardList::OnGetItemImage(long pos) const {
  return isSelected(getCard(pos)) ? 3 : 2;
}

// ----------------------------------------------------------------------------- : Events

void SelectCardList::toggle(const CardP& card) {
  if (isSelected(card)) {
    selected.erase(card);
  } else {
    selected.insert(card);
  }
}

void SelectCardList::toggleSelected(bool select) {
  for (long i = GetFirstSelected(); i != -1; i = GetNextSelected(i)) {
    if (select) {
      selected.insert(getCard(i));
    } else {
      selected.erase(getCard(i));
    }
    RefreshItem(i);
  }
}

void SelectCardList::onKeyDown(wxKeyEvent& ev) {
  if (selected_item_pos == -1 || !selected_item) {
    // no selection
    ev.Skip();
    return;
  }
  switch (ev.GetKeyCode()) {
    case WXK_SPACE: {
      toggleSelected(!isSelected(getCard()));
      break;
    }
    case WXK_NUMPAD_ADD: case '+': {
      toggleSelected(true);
      break;
    }
    case WXK_NUMPAD_SUBTRACT: case '-': {
      toggleSelected(false);
      break;
    }
    default:
      ev.Skip();
  }
}

void SelectCardList::onLeftDown(wxMouseEvent& ev) {
  int flags;
  long item = HitTest(wxPoint(ev.GetX(), ev.GetY()), flags);
  if (flags == wxLIST_HITTEST_ONITEMICON) {
    // only clicking the icon toggles
    if (IsSelected(item)) {
      // if multiple items are selected in the view (regardless of checkbox status), check/uncheck them all
      toggleSelected(!isSelected(getCard(item)));
      return; // don't change selection
    } else {
      toggle(getCard(item));
      RefreshItem(item);
    }
  }
  ev.Skip();
}

BEGIN_EVENT_TABLE(SelectCardList, CardListBase)
  EVT_KEY_DOWN       (SelectCardList::onKeyDown)
  EVT_LEFT_DOWN      (SelectCardList::onLeftDown)
END_EVENT_TABLE  ()
