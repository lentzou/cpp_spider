//
// FileLog.cpp for FileLog in /home/minikali/projects/cpp/cpp_test/src
//
// Made by minikali
// Login   <remi.lak@epitech.eu>
//
// Started on  Tue Oct  3 11:29:48 2017 minikali
// Last update Sun Oct  8 22:26:27 2017 florian lentz
//

#include <iostream>
#include "FileLog.hpp"

FileLog::FileLog(sf::RenderWindow &window) :
  _window(window),
  _head(NULL),
  _explorerBg(sf::Vector2f(WIDTH / (100 / EXPLORER_WIDTH), HEIGHT))
{
  std::string w = "Waiting for client to connect";

    if (!_font.loadFromFile("../fonts/arial.ttf"))
    {
      throw "Cannot load fonts";
    }
    _explorerBg.setFillColor(sf::Color(80, 80, 80));
  _waiting.setString(w);
  _waiting.setCharacterSize(CH_SIZE);
  _waiting.setFont(_font);
  _waiting.setColor(sf::Color::White);
  _waiting.setPosition((WIDTH / 2) - (w.length() * (CH_SIZE / 2)), HEIGHT / 2);
  _fileContent.setCharacterSize(CH_SIZE);
  _fileContent.setFont(_font);
  _fileContent.setColor(sf::Color::White);
  _fileName.setCharacterSize(CH_SIZE);
  _fileName.setFont(_font);
}

FileLog::~FileLog()
{

}

void			FileLog::drawLogName()
{
    s_node		*tmp = _head;
  float			x, y;

  _window.draw(_explorerBg);
  x = 10;
  y = 0;
  _fileName.setString(tmp->_name);
  if (!tmp->_selected)
    _fileName.setColor(sf::Color(40, 40, 40));
  else
    _fileName.setColor(sf::Color(120, 120, 120));
  _fileName.setPosition(x, y);
  _window.draw(_fileName);
  y += SPACE_LINE;
  tmp = tmp->next;
  while (tmp != _head)
    {
      _fileName.setString(tmp->_name);
      if (!tmp->_selected)
	_fileName.setColor(sf::Color(40, 40, 40));
      else
	_fileName.setColor(sf::Color(120, 120, 120));
      _fileName.setPosition(x, y);
      _window.draw(_fileName);
      y += SPACE_LINE;
      tmp = tmp->next;
    }
}

bool			FileLog::addLog(std::string name)
{
  s_node		*newElem;

  try
    {
      newElem = new s_node;
    }
  catch (const std::bad_alloc &ba)
    {
      std::cout << "bad_alloc caught: " << ba.what() << std::endl;
      return false;
    }
  newElem->_name = name;
  newElem->_selected = false;
  newElem->_text.setCharacterSize(CH_SIZE);
  newElem->_text.setFont(_font);
  newElem->next = newElem;
  newElem->prev = newElem;
  if (!_head)
    {
      newElem->_selected = true;
      _head = newElem;
    }
  else
    {
      newElem->next = _head;
      newElem->prev = _head->prev;
      _head->prev->next = newElem;
      _head->prev = newElem;
    }
  return true;
}

s_node		*FileLog::getLogByName(std::string name)
{
  s_node	*tmp = _head;

  if (!_head)
    return 0;
  if (tmp->_name == name)
    return tmp;
  tmp = tmp->next;
  while (tmp != _head)
    {
      if (tmp->_name == name)
  	return tmp;
      tmp = tmp->next;
    }
  return 0;
}

void			FileLog::selectNext()
{
  s_node		*tmp = _head;

  if (_head)
    {
      if (tmp->_selected == true)
	{
	  tmp->_selected = false;
	  tmp->next->_selected = true;
	  return ;
	}
      tmp = tmp->next;
      while (tmp != _head)
	{
	  if (tmp->_selected == true)
	    {
	      tmp->_selected = false;
	      tmp->next->_selected = true;
	      return ;
	    }
	  tmp = tmp->next;
	}
    }
}

void			FileLog::selectPrev()
{
  s_node		*tmp = _head;
  if (_head)
    {
      if (tmp->_selected == true)
	{
	  tmp->_selected = false;
	  tmp->prev->_selected = true;
	  return ;
	}
      tmp = tmp->prev;
      while (tmp != _head)
	{
	  if (tmp->_selected == true)
	    {
	      tmp->_selected = false;
	      tmp->prev->_selected = true;
	      return ;
	    }
	  tmp = tmp->prev;
	}
    }
}

s_node		*FileLog::getSelected() const
{
  s_node	*tmp = _head;

  if (!_head)
    return 0;
  if (tmp->_selected == true)
    return tmp;
  tmp = tmp->next;
  while (tmp != _head)
    {
      if (tmp->_selected == true)
	return tmp;
      tmp = tmp->next;
    }
  return (0);
}

void				FileLog::drawFile()
{
    std::string tmp;
  s_node			*node = getSelected();
  std::string			buf;
  std::ifstream			stream(node->_name);
  float				x = WIDTH / (100 / EXPLORER_WIDTH) + SPACE_LINE;
  float				y = 0;
  std::deque<std::string>	deq;

  if (!stream.is_open())
    {
      std::cout << "could not open file" << std::endl;
    }
  else
    {
      while (getline(stream, buf))
	{
	  if (buf.length() > (WIDTH_CONTENT / CH_SIZE) * 2)
	    {
	      while (buf.length() > (WIDTH_CONTENT / CH_SIZE) * 2)
		{
		  tmp = buf.substr(0, (WIDTH_CONTENT / CH_SIZE) * 2);
		  tmp.push_back('\\');
		  deq.push_back(tmp);
		  buf = buf.substr((WIDTH_CONTENT / CH_SIZE) * 2);
		}
	      deq.push_back(buf);
	    }
	  else
	    deq.push_back(buf);
	  while (deq.size() > (HEIGHT / CH_SIZE) - 1)
	    deq.pop_front();
	}
      stream.close();
      while (deq.size() != 0)
	{
	  _fileContent.setString(deq.front());
	  _fileContent.setPosition(x, y);
	  _window.draw(_fileContent);
	  y += SPACE_LINE;
	  deq.pop_front();
	}
    }
}

s_node		*FileLog::getList() const
{
  return _head;
}

void			FileLog::drawNull()
{
  _window.draw(_waiting);
}
