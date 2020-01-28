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
	// бс(бс)бсбс
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
	// бс(бс)бс
	//      бс
	dic_block_rot['J'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(1, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, -1), P(1, -1)}
		}
	);
	prototypes['J'] = std::make_unique<BlockObject>(dic_block_rot['J'].get(), Color::blue);

	// L-block 
	// бс(бс)бс
	// бс
	dic_block_rot['L'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(-1, 1), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -1), P(-1, -1), P(0, 0), P(0, 1)}
			, std::vector<Point>{P(1, 0), P(1, -1), P(0, 0), P(-1, 0)}
			, std::vector<Point>{P(0, 1), P(1, 1), P(0, 0), P(0, -1)}
		}
	);
	prototypes['L'] = std::make_unique<BlockObject>(dic_block_rot['L'].get(), Color::white);

	// O-block 
	// бс(бс)
	// бс бс
	dic_block_rot['O'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
		}
	);
	prototypes['O'] = std::make_unique<BlockObject>(dic_block_rot['O'].get(), Color::yellow);

	// S-block 
	//   (бс)бс
	// бс бс
	dic_block_rot['S'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, -1), P(1, -1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(1, 0), P(1, 1)}
		}
	);
	prototypes['S'] = std::make_unique<BlockObject>(dic_block_rot['S'].get(), Color::green);


	// T-block 
	// бс(бс)бс
	//    бс
	dic_block_rot['T'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(0, 1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, -1), P(-1, 0)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(0, -1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, 1), P(1, 0)}
		}
	);
	prototypes['T'] = std::make_unique<BlockObject>(dic_block_rot['T'].get(), Color::margenta);

	// Z-block 
	// бс(бс)
	//    бсбс
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
	auto iter = prototypes.begin();
	std::advance(iter, rand_between(0, prototypes.size()));
	return make_block(iter->second.get());
}

std::unique_ptr<BlockObject> Tetris::make_block_key(const char key) noexcept
{
	auto prototype_block = prototypes[key].get();
	return make_block(prototypes[key].get());
}

std::unique_ptr<BlockObject> Tetris::make_block(const BlockObject& block) noexcept
{
	return std::make_unique<BlockObject>(block_index, get_start_point(block), block);
}

TETRIS_END
