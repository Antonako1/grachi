#ifndef MAIN_H
#define MAIN_H

#define VERSION "0.0.1"

// absolute path, pointing to exe's directory
extern std::string project_root_path;

// absolute path, points to %USERPROFILE%\Documents\grachi\         ---
extern std::string project_in_home_docs;

/*+++
When on debug, these are prefixed with project_root_path.
On release they are prefixed with project_in_home_docs
---*/
// absolute path, pointing to: \assets\data\            ---
extern std::string atrc_path;
// absolute path, pointing to \assets\images\           ---
extern std::string image_path;
// absolute path, pointing to \assets\audio\            ---
extern std::string audio_path;

// delta time in seconds
extern float dt;

#include <sfml/System/Time.hpp>
// Current program uptime in seconds
extern sf::Time sec;

#endif // MAIN_H
