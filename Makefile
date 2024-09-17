CFLAGS += -Wall -Wextra -Werror -std=c++20 -march=native -O3

ifeq ($(DEBUG),true)
  CFLAGS += -g
endif

solver: solver.cpp
	$(CXX) "$@.cpp" -o "$@" $(CFLAGS)

.PHONY: clean
clean:
	@rm -fv solver
