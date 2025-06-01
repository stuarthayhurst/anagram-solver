CXXFLAGS += -Wall -Wextra -Werror -Wpedantic -std=c++20 -march=native -O3

ifeq ($(DEBUG),true)
  CXXFLAGS += -g -fno-omit-frame-pointer -fsanitize=address,undefined
endif

solver: solver.cpp
	$(CXX) "$@.cpp" -o "$@" $(CXXFLAGS)

.PHONY: clean
clean:
	@rm -fv solver
