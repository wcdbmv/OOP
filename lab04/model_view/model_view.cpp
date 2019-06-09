#include "model_view.hpp"

void ModelView::AddView(const Model& model) {
  models_.push_back(model);
}

void ModelView::CheckOutOfRange(size_t index) const {
  if (index > models_.size())
    throw ModelViewOutOfRangeException();
}

void ModelView::RemoveView(size_t index) {
  CheckOutOfRange(index);

  models_.erase(index);
}
const Model& ModelView::operator[](size_t index) const {
  CheckOutOfRange(index);

  return models_[index];
}


