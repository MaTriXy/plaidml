// Copyright 2018, Intel Corp.

#pragma once

#include <string>
#include <vector>

#include "tile/stripe/stripe.h"

namespace vertexai {
namespace tile {
namespace codegen {

struct StencilIndex {
  std::string name;
  int size;
  std::vector<int> out_strides;
  std::vector<int> in_strides;
};

struct StencilSpec {
  std::string name;
  size_t startup_cost;
  std::vector<StencilIndex> idxs;
};

struct StencilIndexMatch {
  std::string block_idx_name;
  std::string stencil_idx_name;
  uint64_t value;
};

struct StencilMatch {
  std::string name;
  size_t cost;
  std::vector<StencilIndexMatch> idxs;
  bool is_fallback;
};

std::ostream& operator<<(std::ostream& os, const StencilMatch& match);
bool operator==(const StencilMatch& lhs, const StencilMatch& rhs);
bool operator<(const StencilMatch& lhs, const StencilMatch& rhs);

StencilMatch FindBestStencil(const std::vector<StencilSpec>& specs, stripe::Block* block);

struct TileSpec {
  std::string name;
  TileShape shape;
  stripe::Location loc;
};

void ApplyTile(stripe::Block* inner, const TileSpec& spec, bool elide_trivial = true);

typedef std::function<TileSpec(stripe::Block* block)> TileGenerator;
void TilePass(stripe::Block* block, const TileGenerator& generator);
void TilePass(stripe::Block* block, const std::vector<StencilSpec>& specs);

}  // namespace codegen
}  // namespace tile
}  // namespace vertexai
