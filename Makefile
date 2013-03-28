#
# Author: Zex <top_zlynch@yahoo.com>
#

TARGET    = oneset twoset
LOGS       = *.log *.debug

CC 	  = g++
CXXFLAGS  = -std=c++11 -g3
LDFLAGS   = -lpthread

all: $(TARGET)

%: %.cpp

clean:
	rm -f $(TARGET) $(LOGS)
