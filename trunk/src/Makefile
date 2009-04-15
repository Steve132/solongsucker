OBJ=AppError.o Bargain.o Board.o ChipMsg.o CustomPlayer.o Hand.o IOMgmt.o MoveProposal.o Pile.o Player.o SimMgmt.o SoLongSuckerApp.o

all : SoLongSuckerApp

SoLongSuckerApp : $(OBJ)
	$(CXX) $(OBJ) -o SoLongSuckerApp $(CXXFLAGS)

clean :
	rm -f *.o SoLongSuckerApp

