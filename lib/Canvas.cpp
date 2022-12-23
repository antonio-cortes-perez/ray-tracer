#include "Canvas.h"

#include <sstream>

using namespace ray_tracer;

static int scale(float f) {
  if (f < 0)
    return 0;
  if (f > 1)
    return 255;
  return roundf(f * 255);
}

static std::vector<std::string> split(std::string line) {
  std::vector<std::string> lines;
  while (line.size() > 70) {
    int i = 69;
    while (line[i] != ' ')
      --i;
    lines.push_back(line.substr(0, i));
    line = line.substr(i + 1);
  }
  if (!line.empty()) {
    lines.push_back(line);
  }
  return lines;
}

std::string Canvas::toPPM() {
  std::stringstream ss;
  std::stringstream line;
  ss << "P3\n";
  ss << std::to_string(width) << " " << std::to_string(height) << "\n";
  ss << "255\n";
  int col = 0;
  for (const Color &c : v) {
    line << std::to_string(scale(c.r)) << " ";
    line << std::to_string(scale(c.g)) << " ";
    line << std::to_string(scale(c.b));
    if (++col < width) {
      line << " ";
    } else {
      for (const std::string &str : split(line.str())) {
        ss << str << "\n";
      }
      col = 0;
      line.str("");
    }
  }
  return ss.str();
}
