//
// CoreGraph.hpp for CoreGraph in /home/minikali/projects/cpp/cpp_test/inc
// 
// Made by minikali
// Login   <remi.lak@epitech.eu>
// 
// Started on  Mon Oct  2 15:51:30 2017 minikali
// Last update Sun Oct  8 16:02:02 2017 minikali
//

#ifndef _COREGRAPH_HPP_
# define _COREGRAPH_HPP_

# include <SFML/Graphics.hpp>
# include <iostream>
# include <string>
# include <map>
# include <stack>
# include <thread>
# include <mutex>
# include "FileLog.hpp"

extern std::stack<std::string> files;
extern std::mutex m;
extern bool stop;

class					CoreGraph
{
private:
  int					_width;
  int					_height;
  sf::RenderWindow			_window;
  FileLog				_fileLog;
  
public:
  CoreGraph(int width = 1200, int height = 800);
  ~CoreGraph();

  void					processInput();
  void					update();
  void					render();
  
  void					startGraphMode();
  void					addLogFile(std::string fileName);
};

#endif /* !_COREGRAPH_HPP_ */
