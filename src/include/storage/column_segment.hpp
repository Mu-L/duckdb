//===----------------------------------------------------------------------===//
//                         DuckDB
//
// storage/column_segment.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "storage/block.hpp"
#include "storage/segment_tree.hpp"

namespace duckdb {
class BlockManager;

class ColumnSegment : public SegmentBase {
public:
	//! Initialize a column segment from a specific block
	ColumnSegment(BlockManager *manager, block_id_t block_id, index_t offset, count_t count, index_t start);
	//! Initialize an empty in-memory column segment
	ColumnSegment(index_t start);

	//! The block id to load the data from (if any)
	block_id_t block_id;
	//! The offset into the block
	index_t offset;
	//! A pointer to the next column segment (if any)
	unique_ptr<ColumnSegment> next;
public:
	//! Returns a pointer to the data of the column segment
	data_ptr_t GetData();
private:
	// The block manager
	BlockManager *manager;
	//! The data of the column segment
	unique_ptr<Block> block;
	//! Lock to get the data of the block
	std::mutex data_lock;
};

} // namespace duckdb
