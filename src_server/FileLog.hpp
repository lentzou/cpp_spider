//
// FileLog.hpp for FileLog in /home/minikali/projects/cpp/cpp_test/inc
// 
// Made by minikali
// Login   <remi.lak@epitech.eu>
// 
// Started on  Tue Oct  3 11:26:39 2017 minikali
// Last update Fri Oct  6 15:47:54 2017 minikali
//

#ifndef _FILELOG_HPP_
# define _FILELOG_HPP_

# include <deque>
# include <fstream>
# include <iostream>
# include <SFML/Graphics.hpp>

# define WIDTH (1200)
# define HEIGHT (800)
# define WIDTH_CONTENT ((WIDTH / 5) * 4)
# define EXPLORER_WIDTH (20) //in %
# define SPACE_LINE (20) //in px
# define CH_SIZE (20) //in px

typedef struct		t_node
{
  std::string		_name;
  sf::Text		_text;
  bool			_selected;
  struct t_node		*next;
  struct t_node		*prev;
}			s_node;

class			FileLog
{
private:
  sf::RenderWindow	&_window;
  s_node		*_head;
  sf::Font		_font;
  sf::RectangleShape	_explorerBg;
  sf::Text		_waiting;
  sf::Text		_fileContent;
  sf::Text		_fileName;

public:
  FileLog(sf::RenderWindow &window);
  ~FileLog();

  void			drawLogName();
  bool			addLog(const std::string &name);
  s_node		*getLogByName(const std::string &name);
  s_node		*getSelected() const;
  void			selectNext();
  void			selectPrev();
  void			drawFile();
  void			drawNull();
  s_node		*getList() const;
};

#endif /* !_FILELOG_HPP_ */
