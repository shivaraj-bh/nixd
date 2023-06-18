#pragma once

#include "Parser.tab.h"

namespace nixd {

using namespace nix;

std::unique_ptr<ParseData> parse(char *Text, size_t Length, Pos::Origin Origin,
                                 const SourcePath &BasePath, EvalState &State,
                                 std::shared_ptr<StaticEnv> Env);

inline std::unique_ptr<ParseData> parse(char *Text, size_t Length,
                                        Pos::Origin Origin,
                                        const SourcePath &BasePath,
                                        EvalState &State) {
  return parse(Text, Length, std::move(Origin), BasePath, State,
               State.staticBaseEnv);
}

inline std::unique_ptr<ParseData> parse(std::string Text, Pos::Origin Origin,
                                        const SourcePath &BasePath,
                                        EvalState &State,
                                        std::shared_ptr<StaticEnv> Env) {
  Text.append("\0\0", 2);
  return parse(Text.data(), Text.length(), std::move(Origin), BasePath, State,
               std::move(Env));
}

inline std::unique_ptr<ParseData> parse(std::string Text, Pos::Origin Origin,
                                        const SourcePath &BasePath,
                                        EvalState &State) {
  Text.append("\0\0", 2);
  return parse(Text.data(), Text.length(), std::move(Origin), BasePath, State);
}

} // namespace nixd