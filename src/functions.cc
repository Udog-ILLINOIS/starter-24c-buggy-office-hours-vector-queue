#include "functions.hpp"

#include <iostream>
#include <random>

constexpr int kRandomMin = 5;
constexpr int kRandomMax = 20;

void AddStudent(OfficeHoursQueue& queue, const Student& student) {
  queue.student_queue.push_back(student);
  queue.student_queue.back().arrival_order = queue.student_arrival_counter;
  queue.student_arrival_counter += 1;

  unsigned int i = queue.student_queue.size() - 1;
  while (i > 0) {
    Student curr = queue.student_queue[i];
    Student prev = queue.student_queue[i - 1];
    if (curr.attendance_percentage > prev.attendance_percentage) {
      Student temp = queue.student_queue[i - 1];
      queue.student_queue[i - 1] = queue.student_queue[i];
      queue.student_queue[i] = temp;
      i--;
    } else if (curr.attendance_percentage == prev.attendance_percentage) {
      if (curr.arrival_order < prev.arrival_order) {
        Student temp = queue.student_queue[i - 1];
        queue.student_queue[i - 1] = queue.student_queue[i];
        queue.student_queue[i] = temp;
        i--;
      } else {
        break;
      }
    } else {
      break;
    }
  }
}

void AddStaff(OfficeHoursQueue& queue, const Staff& staff) {
  queue.staff_queue.push_back(staff);
  queue.staff_queue.back().arrival_order = queue.staff_arrival_counter;
  queue.staff_arrival_counter += 1;

  unsigned int index = queue.staff_queue.size() - 1;
  while (index > 0) {
    const Staff& current = queue.staff_queue[index];
    const Staff& previous = queue.staff_queue[index - 1];

    if (current.encounter_count > previous.encounter_count) {
      Staff temp = queue.staff_queue[index - 1];
      queue.staff_queue[index - 1] = queue.staff_queue[index];
      queue.staff_queue[index] = temp;
      index--;
    } else if (current.encounter_count == previous.encounter_count) {
      if (current.arrival_order < previous.arrival_order) {
        Staff temp = queue.staff_queue[index - 1];
        queue.staff_queue[index - 1] = queue.staff_queue[index];
        queue.staff_queue[index] = temp;
        index--;
      } else if (current.total_help_time == previous.total_help_time) {
        if (current.arrival_order < previous.arrival_order) {
          Staff temp = queue.staff_queue[index - 1];
        queue.staff_queue[index - 1] = queue.staff_queue[index];
        queue.staff_queue[index] = temp;
        index--;
        } else {
        break;
        }
      } else {
        break;
      }
    } else {
      break;
    }
  }
}

void HelpNextStudent(OfficeHoursQueue& queue) {
  if (queue.student_queue.empty()) {
    std::cout << "No students in queue.\n";
    return;
  }
  if (queue.staff_queue.empty()) {
    std::cout << "No staff available.\n";
    return;
  }

  Student student = queue.student_queue[0];
  queue.student_queue.erase(queue.student_queue.begin());

  // Generate random help time between kRandomMin and kRandomMax minutes
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(kRandomMin, kRandomMax);
  int help_time = dist(gen);

  Staff staff = queue.staff_queue[0];
  queue.staff_queue.erase(queue.staff_queue.begin());

  staff.encounter_count++;
  staff.total_help_time += help_time;
  // AddStaff(queue, staff);

  std::cout << "Staff " << staff.name << " helped student " << student.name
            << " for " << help_time << " minutes.\n";
  AddStaff(queue, staff);
}

bool IsStudentQueueEmpty(const OfficeHoursQueue& queue) {
  return queue.student_queue.empty();
}

bool IsStaffQueueEmpty(const OfficeHoursQueue& queue) {
  return queue.staff_queue.empty();
}