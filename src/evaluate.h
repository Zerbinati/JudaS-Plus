/*
  JudaS, a UCI chess playing engine derived from Stockfish
  Copyright (C) 2004-2025 The Stockfish developers (see AUTHORS file)

  JudaS is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  JudaS is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EVALUATE_H_INCLUDED
#define EVALUATE_H_INCLUDED

#include <string>
#include <unordered_map>

#include "types.h"
#include "position.h"

namespace Judas {

class Position;

namespace Eval {

// Dichiarazioni delle funzioni
int determine_phase(const Position& pos, int totalMaterial);
void applyStyle(const std::string& style);

// Dichiarazione dei parametri globali per gli stili
					  
extern int KingSafetyWeight;
extern int PieceActivityWeight;
extern int PawnStructureWeight;

void resetParametersToDefault();

// Dichiarazioni delle nuove funzioni aggiunte in evaluate.cpp
int blend_nnue_with_simple(int nnue, int simpleEval, int nnueComplexity, int materialImbalance);
int dampened_shuffling(int shuffling);

constexpr inline int SmallNetThreshold = 1165, PsqtOnlyThreshold = 2500;

std::string trace(Position& pos);

int   simple_eval(const Position& pos, Color c);
Value evaluate(const Position& pos);

// The default net name MUST follow the format nn-[SHA256 first 12 digits].nnue
// for the build process (profile-build and fishtest) to work. Do not change the
// name of the macro, as it is used in the Makefile.
#define EvalFileDefaultNameBig "nn-1c0000000000.nnue"
#define EvalFileDefaultNameSmall "nn-37f18f62d772.nnue"

namespace NNUE {

    extern int StrategyMaterialWeight;
    extern int StrategyPositionalWeight;

    enum NetSize : int;

    void init();
    void verify();
    void update_weights(int phase);

}  // namespace NNUE

struct EvalFile {
    std::string option_name;
    std::string default_name;
    std::string selected_name;
};

extern std::unordered_map<NNUE::NetSize, EvalFile> EvalFiles;

}  // namespace Eval

}  // namespace Judas

#endif  // #ifndef EVALUATE_H_INCLUDED
