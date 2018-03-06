////
//// CoreGraph.cpp for CoreGraph in /home/minikali/projects/cpp/cpp_test/src
//// 
//// Made by minikali
//// Login   <remi.lak@epitech.eu>
//// 
//// Started on  Mon Oct  2 15:54:54 2017 minikali
//// Last update Sun Oct  8 16:02:21 2017 minikali
////

#include "CoreGraph.hpp"

std::stack<std::string> files;
std::mutex m;
bool stop = false;

CoreGraph::CoreGraph(int width, int height) :
  _width(width),
  _height(height),
  _window(sf::VideoMode(width,height), "Spider"),
  _fileLog(_window)
{
}

CoreGraph::~CoreGraph()
{

}

void					CoreGraph::startGraphMode()
{
  while (_window.isOpen())
    {
      CoreGraph::processInput();
      CoreGraph::update();
      CoreGraph::render();
    }
}

void					CoreGraph::addLogFile(const std::string& fileName)
{
  if (_fileLog.getLogByName(fileName) == 0)
    {
      _fileLog.addLog(fileName);
    }
}

void					CoreGraph::processInput()
{
  sf::Event event;

  while (_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed || stop == true)
	_window.close();
      else if (event.type == sf::Event::KeyPressed)
	{
	  if (event.key.code == sf::Keyboard::Escape)
	    {
	      _window.close();
	    }
	  else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Up)
	    {
	      _fileLog.selectPrev();
	    }
	  else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Down)
	    {
	      _fileLog.selectNext();
	    }
	}
    }
}

void					CoreGraph::update()
{
  m.lock();
  while (!files.empty())
    {
      addLogFile(files.top());
      files.pop();
    }
  m.unlock();
  if (!_fileLog.getList())
    _fileLog.drawNull();
  else
    {
      _fileLog.drawLogName();
      _fileLog.drawFile();
    }
}

void					CoreGraph::render()
{
  _window.display();
  _window.clear();
}
