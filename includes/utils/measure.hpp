/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace ama {
namespace utils {

class StatsMeter {
 public:
  /**
   * Default constructor
   * Prepares the vector and the counter before the action
   */
  StatsMeter() : values_{}, min_value_{100.}, max_value_{0.}, mean_{0.f} {}

  /**
   * Default destructor
   */
  ~StatsMeter();
  /**
   * Register a new measurement
   * It register the reference value and the measurement value. It computes the
   * error and saves it into the values vector.
   * @tparam T type of the measurement type
   * @param reference reference value take as a theoretical value
   * @param measured measured value take as the approximation value
   * @param normalisation normalisation value
   */
  template <typename T>
  void Register(const double reference, const T measured,
                const double normalisation);

  /**
   * Print the results
   * Computes the statistical values and prints them out through stdout
   */
  void Print() const;

  /**
   * Compute the histogram of an array of differences.
   * The values are ranged from 0 - max and absolutely evaluated.
   * @param bins number of bins of the histogram
   * @param max max number of the histogram
   */
  std::vector<int> compute_histogram(const int bins, const double max) const;

 private:
  std::vector<double> values_;
  double min_value_;
  double max_value_;
  double mean_;
};

template <typename T>
inline void StatsMeter::Register(const double reference, const T measured,
                                 const double normalisation) {
  double difference = std::abs(reference - static_cast<double>(measured)) /
                      std::abs(normalisation);

  /* Pre-compute min, max to avoid as many runs as possible */
  min_value_ = std::min(difference, min_value_);
  max_value_ = std::max(difference, max_value_);

  /* Compute the mean */
  mean_ *= (static_cast<double>(values_.size()) /
            static_cast<double>(values_.size() + 1));
  mean_ += (difference / static_cast<double>(values_.size() + 1));

  /* Emplace values for the std */
  values_.push_back(std::move(difference));
}

inline StatsMeter::~StatsMeter() { Print(); }

inline std::vector<int> StatsMeter::compute_histogram(const int bins,
                                                      const double max) const {
  /* Allocate and initialise histogram */
  std::vector<int> histogram(bins, 0.);
  double quantum = max / static_cast<double>(bins);

  /* Compute the histogram */
  for (const double val : values_) {
    int index = static_cast<int>(std::abs(val) / quantum);
    if (index >= histogram.size()) continue;
    ++histogram.at(index);
  }

  return histogram;
}

inline void StatsMeter::Print() const {
  const int bins = 500;
  const double max_hist = 0.3;
  /* Copy vector */
  decltype(values_) stdvalues(values_);
  decltype(mean_) mean{mean_};
  std::size_t size{values_.size()};

  /* Prepare lambda for the per-element transformation: (xi - mean)^2 / N */
  auto per_element_transform = [=](double xi) -> double {
    double acc = xi - mean;
    return acc * acc / size;
  };

  /* Compute the std */
  std::transform(values_.begin(), values_.end(), stdvalues.begin(),
                 per_element_transform);

  double variance = std::accumulate(stdvalues.begin(), stdvalues.end(), 0.);
  double stdval = std::sqrt(variance);

  /* Compute histogram */
  std::vector<int> hist = compute_histogram(bins, max_hist);

  std::cout << " ------------------------------------------------ " << std::endl
            << "| Measurement results                            |" << std::endl
            << " ------------------------------------------------ " << std::endl
            << ">> TestMinVal: " << min_value_ << std::endl
            << ">> TestMaxVal: " << max_value_ << std::endl
            << ">> TestMeanVal: " << mean_ << std::endl
            << ">> TestStdVal: " << stdval << std::endl
            << ">> TestVarVal: " << variance << std::endl;

  /* Print histogram */
  std::cout << "Hist " << bins << " bins " << static_cast<int>(max_hist * 100)
            << "%: [";
  for (const int val : hist) {
    std::cout << val << "; ";
  }
  std::cout << "]" << std::endl;

  std::cout << " ------------------------------------------------ "
            << std::endl;
}
}  // namespace utils
}  // namespace ama
