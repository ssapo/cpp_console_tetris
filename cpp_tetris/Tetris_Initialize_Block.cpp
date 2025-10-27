#include "Tetris.h"
#include "Game.h"
#include "Board.h"
#include "Renderer.h"
#include "Updater.h"
#include "Cell.h"
#include "BlockObject.h"

TETRIS_START

// https://imgur.com/a/GZae9T8
bool Tetris::initialize_blocks() noexcept
{
	// I-block 
	// ()
	//
	dic_block_rot['I'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(2, 0), P(-1, 0), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, 2), P(0, 1), P(0, 0), P(0, -1)}
			, std::vector<Point>{P(2, 0), P(-1, 0), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, 2), P(0, 1), P(0, 0), P(0, -1)}
		}
	);
	prototypes['I'] = std::make_unique<BlockObject>(dic_block_rot['I'].get(), Color::cyan);

	// J-block 
	// ()
	//      
	dic_block_rot['J'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(1, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, -1), P(1, -1)}
		}
	);
	prototypes['J'] = std::make_unique<BlockObject>(dic_block_rot['J'].get(), Color::blue);

	// L-block 
	// ()
	// 
	dic_block_rot['L'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(-1, 1), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -1), P(-1, -1), P(0, 0), P(0, 1)}
			, std::vector<Point>{P(1, 0), P(1, -1), P(0, 0), P(-1, 0)}
			, std::vector<Point>{P(0, 1), P(1, 1), P(0, 0), P(0, -1)}
		}
	);
	prototypes['L'] = std::make_unique<BlockObject>(dic_block_rot['L'].get(), Color::white);

	// O-block 
	// ()
	//  
	dic_block_rot['O'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
		}
	);
	prototypes['O'] = std::make_unique<BlockObject>(dic_block_rot['O'].get(), Color::yellow);

	// S-block 
	//   ()
	//  
	dic_block_rot['S'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, -1), P(1, -1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(1, 0), P(1, 1)}
		}
	);
	prototypes['S'] = std::make_unique<BlockObject>(dic_block_rot['S'].get(), Color::green);


	// T-block 
	// ()
	//    
	dic_block_rot['T'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(0, 1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, -1), P(-1, 0)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(0, -1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, 1), P(1, 0)}
		}
	);
	prototypes['T'] = std::make_unique<BlockObject>(dic_block_rot['T'].get(), Color::margenta);

	// Z-block 
	// ()
	//    
	dic_block_rot['Z'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(1, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(-1, 0), P(-1, 1)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(0, -1), P(-1, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(1, 0), P(1, -1)}
		}
	);
	prototypes['Z'] = std::make_unique<BlockObject>(dic_block_rot['Z'].get(), Color::red);

	return true;
}

std::unique_ptr<BlockObject> Tetris::make_block_random() noexcept
{
	if (prototypes.empty())
	{
		return nullptr;
	}

	auto iter = prototypes.begin();
	std::advance(iter, rand_between(0, static_cast<int>(prototypes.size())));

	auto& prototype = iter->second;
	if (!prototype)
	{
		return nullptr;
	}

	return make_block(*(prototype.get()));
}

std::unique_ptr<BlockObject> Tetris::make_block_key(const char key) noexcept
{
	auto iter = prototypes.find(key);
	if (iter == prototypes.end() || !(iter->second))
	{
		return nullptr;
	}

	return make_block(*(iter->second));
}

std::unique_ptr<BlockObject> Tetris::make_block(const BlockObject& block) noexcept
{
	return std::make_unique<BlockObject>(block_index, get_start_point(block), block);
}

TETRIS_END
