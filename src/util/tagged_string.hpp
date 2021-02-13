//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

/** @file util/tagged_string.hpp
 *
 *  @brief Utility for working with strings with tags
 */
 
// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>

// ----------------------------------------------------------------------------- : Conversion to/from normal string

/// Escaped '<'
const Char ESCAPED_LANGLE = _('\1');

wxUniChar untag_char(wxUniChar c);
wxUniChar tag_char(wxUniChar c);

/// Remove all tags from a string and convert ESCAPED_LANGLE back to normal '<'
/** e.g. "<sym>R</sym> something <i>(note)</i>"
 *  becomes "R something (note)"
 */
String untag(const String&);

/// Remove all tags from a string, but doesn't convert back escape codes
/** untag_no_escape(x) = escape(untag(x)) */
String untag_no_escape(const String&);

/// Remove all tags from a string
/** In addition to what untag() does this function also removes <sep-soft>...</sep-soft>
 */
String untag_hide_sep(const String&);

/// Escapes a String by converting '>' to ESCAPED_LANGLE
String escape(const String&);

/// Convert old style </> close tags to new style </tag> tags
/** This style was used until 0.2.6 */
String fix_old_tags(const String&);

// ----------------------------------------------------------------------------- : Finding tags

/// Returns the position of the tag the given position is in
/** Returns String::npos if pos is not in a tag.
 *  In a tag is:
 *   < t a g >
 *  n y y y y n
 */
[[nodiscard]] size_t tag_start(const String& str, size_t pos);

/// Returns the position just beyond the tag starting at start
[[nodiscard]] size_t skip_tag(const String& str, size_t start);

/// Find the position of the closing tag matching the tag at start
/** If not found returns String::npos */
[[nodiscard]] size_t match_close_tag(const String& str, size_t start);

/// Find the position of the closing tag matching the tag at start
/** Returns the position just after that tag.
 *    match_close_tag_end(s,i) == skip_tag(s, match_close_tag(s,i) )
 *  If not found returns String::npos */
[[nodiscard]] size_t match_close_tag_end(const String& str, size_t start);

/// Find the last start tag before position start
/** If not found returns String::npos */
[[nodiscard]] size_t last_start_tag_before(const String& str, const String& tag, size_t start);

/// Does a string contain a tag at the given location?
/** Only matches if the tag ends one of ">-: " */
[[nodiscard]] bool is_tag(const String& str, size_t pos, const String& tag);

/// Is the given range entirely contained in a given tagged block?
/** If so: return the start position of that tag, otherwise returns String::npos
 *  A tagged block is everything between <tag>...</tag>
 *  Note: this function looks for a positive number of tags, so in for example
 *          <tag><tag></tag>x</tag>
 *        the x is in_tag
 */
[[nodiscard]] size_t in_tag(const String& str, const String& tag, size_t start, size_t end);
/// Boolean returning version of the above
bool is_in_tag(const String& str, const String& tag, size_t start, size_t end);

/// Return the tag at the given position (without the <>)
String tag_at(const String& str, size_t pos);

/// Return the tag at the given position (without the <>)
/** stops at '-', so for "<kw-a>" returns "kw" */
String tag_type_at(const String& str, size_t pos);

/// Matching close tag for a tag
String close_tag(const String& tag);

/// The matching close tag for an open tag and vice versa
String anti_tag(const String& tag);

// ----------------------------------------------------------------------------- : Iterators in tagged strings

// Skip to the end of a tag, it must point to the start of a tag
[[nodiscard]] String::const_iterator skip_tag(String::const_iterator it, String::const_iterator end);

// Skip past all tags
[[nodiscard]] String::const_iterator skip_all_tags(String::const_iterator it, String::const_iterator end);

// Skip past all open/close tags
[[nodiscard]] String::const_iterator skip_all_tags(String::const_iterator it, String::const_iterator end, bool skip_open, bool skip_close);

// Advance an iterator by n positions, not counting tags
// For example: advance_untagged("<b>abc</b>",_,2) = "c</b>"
[[nodiscard]] String::const_iterator advance_untagged(String::const_iterator it, String::const_iterator end, size_t n, bool after_open=false, bool after_close=false);

// Find the position of the closing tag matching the tag at it
// If not found, returns end
[[nodiscard]] String::const_iterator find_close_tag(String::const_iterator it, String::const_iterator end);

/// Does a string contain a tag at the given location?
/** Only matches if the tag in the text ends one of ">-: "
 *  tag should be "<tag" or "</tag"
 */
[[nodiscard]] bool is_tag(String::const_iterator it, String::const_iterator end, const char* tag);

// Length of a string when not counting tags
// For example: untagged_length("<b>abc</b>",_) = 3
[[nodiscard]] size_t untagged_length(String::const_iterator it, String::const_iterator end);

// ----------------------------------------------------------------------------- : Cursor position

/// Directions of cursor movement
enum Movement
{  MOVE_LEFT      = -2  ///< Always move the cursor to the left
,  MOVE_LEFT_OPT  = -1  ///< Move the cursor to the left, but a position inside a tag is the same as that before
,  MOVE_MID       =  0  ///< Move in whichever direction the distance to move is shorter (TODO: define shorter)
,  MOVE_RIGHT_OPT =  1  ///< Move the cursor to the left, but a position inside a tag is the same as that after
,  MOVE_RIGHT     =  2  ///< Always move the cursor to the right
};

/// Find the cursor position corresponding to the given character index.
/** A cursor position always corresponds to a valid place to type text.
 *  The cursor position is rounded to the direction dir.
 */
size_t index_to_cursor(const String& str, size_t index, Movement dir = MOVE_MID);

/// Find the range of character indeces corresponding to the given cursor position
/** The output parameters will correspond to the range [start...end) which are all valid character indices.
 */
void cursor_to_index_range(const String& str, size_t cursor, size_t& begin, size_t& end);

/// Find the character index corresponding to the given cursor position
size_t cursor_to_index(const String& str, size_t cursor, Movement dir = MOVE_MID);


const Char UNTAG_ATOM       = _('\2');
const Char UNTAG_SEP        = _('\3');
const Char UNTAG_ATOM_KWPPH = _('\4');

/// Untag a string for use with cursors, <atom>...</atom> becomes a single character.
/** This string should only be used for cursor position calculations. */
String untag_for_cursor(const String& str);

// ----------------------------------------------------------------------------- : Untagged position

/// Find the tagged position corresponding to the given untagged position.
/** An untagged position in str is a position in untag(str).
 *  @param inside if inside then it prefers to find positions inside tags (after open tags, before close tags)
 *  @param start_index is the position to start at in the string,
 *                     untagged_to_index(s,_,_,i) == untagged_to_index(s.substr(i),_,_)+i
 */
size_t untagged_to_index(const String& str, size_t pos, bool inside, size_t start_index = 0);

/// Find the untagged position corresponding to the given tagged position.
/** An untagged position in str is a position in untag(str).
 */
size_t index_to_untagged(const String& str, size_t index);

// ----------------------------------------------------------------------------- : Global operations

/// Remove all instances of a tag and its close tag, but keep the contents.
/** tag doesn't have to be a complete tag, for example remove_tag(str, "<kw-")
 *  removes all tags starting with "<kw-".
 */
String remove_tag(const String& str, const String& tag);

/// Remove all instances of tags starting with tag, but not its close tag
String remove_tag_exact(const String& str, const String& tag);

/// Remove all instances of a tag (including contents) from a string
/** tag doesn't have to be a complete tag, for example remove_tag_contents(str, "<kw-")
 *  removes all tags starting with "<kw-".
 */
String remove_tag_contents(const String& str, const String& tag);

// ----------------------------------------------------------------------------- : Updates

/// Return all open or close tags in the given range from a string
/** for example:
 *    if close_tags == false, "text<tag>text</tag>text" --> "<tag>"
 *    if close_tags == true,  "text<tag>text</tag>text" --> "</tag>"
 */
String get_tags(const String& str, size_t start, size_t end, bool open_tags, bool close_tags);

/// Replace a subsection of 'input' with 'replacement'.
/** The section to replace is indicated by [start...end).
 *  This function makes sure tags still match. It also attempts to cancel out tags.
 *  This means that when removing "<x>a</x>" nothing is left,
 *  but with input "<x>a" -> "<x>" and "</>a" -> "</>".
 *  Does not escape the replacement.
 */
String tagged_substr_replace(const String& input, size_t start, size_t end, const String& replacement);

// ----------------------------------------------------------------------------- : Simplification

/// Verify that a string is correctly tagged
/** Ensures that:
 *   - All tags end, i.e. for each '<' there is a matching '>'
 *   - There are no tags containing '<' or whitespace
 *   - For each open tag there is a matching close tag.
 *
 *  In case of an error, shows a warning
 *  Return true if the string is a valid tagged string
 */
bool check_tagged(const String& str, bool check_balance = true);
#ifdef _DEBUG
  #if 0
    #define assert_tagged(...) assert(check_tagged(__VA_ARGS__))
  #else
    #define assert_tagged(...) check_tagged(__VA_ARGS__)
  #endif
#else
  #define assert_tagged(...) do{}while(0)
#endif

/// Simplify a tagged string
/**   - merges adjecent open/close tags: "<tag></tag>" --> ""
 *    - removes overlapping tags: "<i>a<i>b</i>c</i>" --> "<i>abc</i>"
 */
String simplify_tagged(const String& str);

/// Simplify a tagged string by merging adjecent open/close tags
/** e.g. "<tag></tag>" --> ""
 *
 * @param all Merge all tags, if false only merges b,i,sym, and <tag></tag> pairs. But not </tag><tag>.
 */
String simplify_tagged_merge(const String& str, bool all = false);

/// Simplify overlapping formatting tags
/** e.g. "<i>blah<i>blah</i>blah</i>" -> "<i>blahblahblah</i>"
 */
String simplify_tagged_overlap(const String& str);

// ----------------------------------------------------------------------------- : Other utilities

/// Turn straight quotes into curly ones or vice-versa
String curly_quotes(String str, bool curl);

