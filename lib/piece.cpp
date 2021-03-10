#include "piece.hpp"

#include "board.hpp"
#include "constants.hpp"

// _is_white has to be 0 or 1
Piece::Piece(uint8_t _type, uint8_t _is_white) {
	type = _type;
	is_white = _is_white;
}

static void add_rook_moves(Board& board, int x, int y,
		std::vector<std::pair<int, int>>& res)
{
	for (int _x = x - 1; _x >= 0; _x--) {
		res.push_back({_x, y});
		if (board.getPiece(_x, y).type != (uint8_t)Pieces::Empty) break;
	}
	for (int _x = x + 1; _x < 8; _x++) {
		res.push_back({_x, y});
		if (board.getPiece(_x, y).type != (uint8_t)Pieces::Empty) break;
	}
	for (int _y = y - 1; _y >= 0; _y--) {
		res.push_back({x, _y});
		if (board.getPiece(x, _y).type != (uint8_t)Pieces::Empty) break;
	}
	for (int _y = y + 1; _y < 8; _y++) {
		res.push_back({x, _y});
		if (board.getPiece(x, _y).type != (uint8_t)Pieces::Empty) break;
	}
}

static void add_bishop_moves(Board& board, int x, int y,
		std::vector<std::pair<int, int>>& res)
{
	std::vector<std::pair<int, int>> mods = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	for (std::pair<int, int> mod : mods) {
		int dx = std::get<0>(mod), dy = std::get<1>(mod);
		for (int _y = y + dy, _x = x + dx;
				_y >= 0 && _y < 8 && _x >= 0 && _x < 8;
				_y += dy, _x += dx)
		{
			res.push_back({_x, _y});
			if (board.getPiece(_x, _y).type != (uint8_t)Pieces::Empty) break;
		}
	}
}

std::vector<std::pair<int, int>> Piece::get_moves_raw(Board& board, int x, int y) {
	std::vector<std::pair<int, int>> res;
	switch ((Pieces)type) {
	case Pieces::Rook:
		add_rook_moves(board, x, y, res);
		break;

	case Pieces::Bishop:
		add_bishop_moves(board, x, y, res);
		break;

	case Pieces::Queen:
		add_rook_moves(board, x, y, res);
		add_bishop_moves(board, x, y, res);
		break;

	case Pieces::King: {
		std::vector<std::pair<int, int>> mods = {
			{-1, -1}, {-1, 0}, {-1, 1},
			{ 0, -1},          { 0, 1},
			{ 1, -1}, { 1, 0}, { 1, 1},
		};

		for (std::pair<int, int>& mod : mods) {
			int dx = std::get<0>(mod), dy = std::get<1>(mod);
			int _x = x + dx, _y = y + dy;

			if (_x >= 0 && _x < 8 && _y >= 0 && _y < 8) {
				res.push_back({_x, _y});
			}
		}
	}
		break;

	default:
		break;
	}

	return res;
}
