CFLAGS += -Wall -Wextra -Werror -std=c++20 -march=native -flto=auto
ifeq ($(FAST),true)
  CFLAGS += -Ofast
else
  CFLAGS += -O3
endif

ifeq ($(DEBUG),true)
  CFLAGS += -g
endif

solver: solver.cpp
	$(CXX) "$@.cpp" -o "$@" $(CFLAGS)

.PHONY: clean
clean:
	@rm -fv solver
