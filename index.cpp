#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

#define SRC_PATH "/src/"

std::string getFolderPath(const std::string& path, const std::string& name) {
  return path + "/" + name;
}

std::string getFilePath(const std::string& path, const std::string& folder, const std::string& file) {
  return path + folder + "/" + file;
}

void fillFoldersAndFilesNames(std::string* folders, std::string* files, std::string& name) {
  folders[0] = "/utils/types";
  folders[1] = "/ui";
  folders[2] = "/api";

  files[0] = "types.ts";
  files[1] = "style.module.scss";
  files[2] = name + ".tsx";
}

void ask(std::string& path, std::string& name) {
  std::string relativePath;
  std::cout << "Enter path for your component: src/\n";
  std::cin >> relativePath;

  std::cout << "Enter the name of your component" << '\n';
  std::cin >> name;

  path = relativePath[relativePath.length() - 1] == '/'
             ? fs::current_path().generic_string() + SRC_PATH + relativePath
             : fs::current_path().generic_string() + SRC_PATH + relativePath + '/';
  fs::current_path(fs::temp_directory_path());
}

template <typename Stream>
void createFiles(Stream& pStream, const std::string& pathToComponent, std::string* folders, std::string* files,
                 const std::string& componentName) {
  try {
    pStream.open(getFilePath(pathToComponent, folders[0], files[0]).c_str());
    pStream << "export interface I {\n\n";
    pStream << "}" << std::endl;
    pStream.close();
    pStream.clear();
  } catch (std::string error) {
    std::cout << error;
  }

  try {
    pStream.open(getFilePath(pathToComponent, folders[1], files[1]).c_str());
    pStream.close();
    pStream.clear();
  } catch (std::string error) {
    std::cout << error;
  }

  try {
    pStream.open(getFilePath(pathToComponent, folders[1], files[2]).c_str());
    pStream << "import s from './style.module.scss';\n\n";
    pStream << "const " << componentName << " = () => {\n\n";
    pStream << "  return ();\n";
    pStream << "};\n\n";
    pStream << "export default " << componentName << ";" << std::endl;
    pStream.close();
    pStream.clear();
  } catch (std::string error) {
    std::cout << error;
  }
}

int main() {
  std::string currentPath, componentName, pathToComponent;
  std::string* folders = new std::string[3];
  std::string* files = new std::string[3];

  ask(currentPath, componentName);
  fillFoldersAndFilesNames(folders, files, componentName);
  pathToComponent = currentPath + componentName;

  for (int i = 0; i < 3; ++i) {
    fs::create_directories(getFolderPath(pathToComponent, folders[i]));
  }

  std::ofstream fout;

  createFiles(fout, pathToComponent, folders, files, componentName);

  return 0;
}
