/*
 * main.cpp
 *
 *  Created on: May 26, 2020
 *      Author: fading
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>


class StreamAndLine {
public:
  std::string line_;
  std::ifstream* stream_;

  StreamAndLine(const std::string& line, std::ifstream* stream)
    : line_(line),
      stream_(stream) {
  }

  StreamAndLine()
    : stream_(nullptr) {
  }
};


int s_file_index(0);
std::vector<std::string> s_file_list;

void WriteFile(const std::vector<std::string>& sorted_lines) {
  std::string file_name = std::to_string(s_file_index++) + ".txt";
  s_file_list.push_back(file_name);
  std::ofstream out_file(file_name);
  for (auto& line : sorted_lines) {
    out_file << line << '\n';
  }
}

void UpdateElement(std::vector<StreamAndLine>& datas,
    std::ifstream* pos, std::string new_line) {
  for (int i = 0; i < datas.size(); ++i) {
    if (datas[i].stream_ == pos) {
      datas[i].line_ = new_line;
      return;
    }
  }

}

int main(int argc, char *argv[]) {
  // Parse argument
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-h" || argv[i] == "--help") {
      std::cout << "Usage:\n";
      std::cout << "./ExternalSort input_file output_file mem_limit\n";
      return 0;
    }
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];
  long long mem_limit(0);
  std::stringstream iss(argv[3]);
  iss >> mem_limit;

  // Algorithm start
  std::ifstream in_file(input_file);
  std::string line;
  std::vector<std::string> part_lines;
  long long mem_usage(0);
  while (std::getline(in_file, line)) {
    mem_usage += line.size();
    part_lines.push_back(std::move(line));
    if (mem_usage >= mem_limit) {
      // Sort normal part
      std::sort(part_lines.begin(), part_lines.end());
      WriteFile(part_lines);
      part_lines.clear();
      mem_usage = 0;
    }
  }
  in_file.close();

  // Sort the final part
  if (!part_lines.empty()) {
    std::sort(part_lines.begin(), part_lines.end());
    WriteFile(part_lines);
    part_lines.clear();
    mem_usage = 0;
  }

  // Apply k-ways merge to get the final result

  // Open all file
  std::vector<std::ifstream*> merge_streams;
  for (const auto& file : s_file_list) {
    merge_streams.push_back(new std::ifstream(file));
  }

  // Extract line data of each file. Find the minimum element and move it to
  // output buffer
  std::vector<StreamAndLine> extracted_datas;
  StreamAndLine minimum_line_data;
  std::string extracted_line;
  bool is_first_iter(true);
  std::ofstream out_file(output_file);
  int no_extracted_line(0);
  int no_written_line(0);
  while (true) {
    for (int i = 0; i < merge_streams.size(); ++i) {
      std::ifstream* stream = merge_streams[i];

      // Extract smallest line of each stream to compare
      if (is_first_iter || minimum_line_data.stream_ == stream) {
        if (!std::getline(*stream, extracted_line)) {
          std::cout << "Call to this scope\n";
          // Delete the stream after it is completely extracted
          merge_streams.erase(merge_streams.begin() + i);
          for (auto it = extracted_datas.begin(); it != extracted_datas.end(); ++it) {
            if (it->stream_ == stream) {
              extracted_datas.erase(it);
              break;
            }
          }
          delete stream;
          break;
        }
        ++no_extracted_line;
        if (minimum_line_data.stream_ == stream) {
          // Just update then break immediately
          UpdateElement(extracted_datas, stream, extracted_line);
          break;
        } else {
          // Add new element
          extracted_datas.push_back(StreamAndLine(extracted_line, stream));
        }
      }
    }

    if (merge_streams.empty()) {
      break;
    }

    // After extract over all stream, now is the time for us to compare and
    // write data to final output
    for (int i = 0; i < extracted_datas.size(); ++i) {
      if (i == 0) {
        minimum_line_data = extracted_datas[i];
      } else if (extracted_datas[i].line_ < minimum_line_data.line_) {
        minimum_line_data = extracted_datas[i];
      }
    }

    // Ok, now write data to final output
    out_file << minimum_line_data.line_ << '\n';
    ++no_written_line;
    is_first_iter = false;
  }

  std::cout << "No extracted lines: " << no_extracted_line << std::endl;
  std::cout << "No written lines: " << no_written_line << std::endl;

  return 0;
}



