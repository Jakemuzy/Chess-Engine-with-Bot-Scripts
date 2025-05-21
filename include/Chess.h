#include <vector>
#include <map>
#include <string>

//  Piece types and Colors definitions 

enum PieceType { BLANK, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum Color { WHITE, BLACK};

struct Move 
{
    int x, y;

    Move(int _x, int _y);

    //  If Move is in a vector containing possible moves
    bool inVector(const std::vector<Move> &moves) const;

    bool operator==(const Move &other) const;

    void print();
};

//  Actual pieces

class ChessPiece
{
protected:
    PieceType type = BLANK;
    Color color = WHITE;
    int value = 0;    
public:
    
    ChessPiece();
    ChessPiece(Color _color);

    Color getColor();
    PieceType getType();

    virtual bool move(int x, int y, int destX, int destY, ChessPiece* board[80]);

    void print();
    std::string printName();
};

class Pawn : public ChessPiece
{
public:
    Pawn(Color _color);
    bool move(int x, int y, int destX, int destY, ChessPiece* board[80]);
};

class Knight : public ChessPiece
{
public:
    Knight(Color _color);
    bool move(int x, int y, int destX, int destY, ChessPiece* board[80]);
};

class Bishop : public ChessPiece
{
public:
    Bishop(Color _color);
    bool move(int x, int y, int destX, int destY, ChessPiece* board[80]);
};

class Rook : public ChessPiece
{
public:
    Rook(Color _color);
    bool move(int x, int y, int destX, int destY, ChessPiece* board[80]);
};

class Queen : public ChessPiece
{
public:
    Queen(Color _color);
    bool move(int x, int y, int destX, int destY, ChessPiece* board[80]);
};

class King : public ChessPiece
{
public:
    King(Color _color);
    bool move(int x, int y, int destX, int destY, ChessPiece* board[80]);
};

//  Chess Board

struct Board
{
    ChessPiece* board[80];

    Board();

    void move(int x, int y, int destX, int destY);

    void print();
};