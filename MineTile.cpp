#include "MineTile.h"

auto MineTile::is_mine() const -> bool {
	return true;
}

auto MineTile::clicked_rep() const -> char {
	return '*';
}
