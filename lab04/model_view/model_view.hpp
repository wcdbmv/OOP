#ifndef LAB04_MODEL_VIEW_MODEL_VIEW_HPP_
#define LAB04_MODEL_VIEW_MODEL_VIEW_HPP_

#include "containers/vector/vector.hpp"
#include "objects/model.hpp"
#include "exceptions/model_view_exceptions.hpp"

class ModelView {
 public:
  ModelView() = default;
  ModelView(ModelView&) = delete;
  ModelView(const ModelView&) = delete;
  ~ModelView() = default;

  void AddView(const Model& model);
  void RemoveView(size_t index);

  const Model& operator[](size_t index) const;

 private:
  void CheckOutOfRange(size_t index) const;

  Vector<Model> models_;
};

#endif  // LAB04_MODEL_VIEW_MODEL_VIEW_HPP_