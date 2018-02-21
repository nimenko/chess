#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <memory>
#include <functional>

#include "asyncaiplayer.h"
#include "chessboard.h"

AsyncAiPlayer::AsyncAiPlayer(int color, int search_depth) :
    AsyncPlayer(color),
    AIPlayer(color, search_depth)
{
}

void AsyncAiPlayer::asyncPrepare(const ChessBoard& board, AsyncPlayer::ReadyHandler handler)
{
    handler();
}

void AsyncAiPlayer::asyncGetMove(const ChessBoard& board, AsyncPlayer::MoveReadyHandler handler)
{
    auto getMoveAsync = [this, &board, handler]()
    {
        Move foundMove;
        getMove(board, foundMove);
        getStrand()->post([foundMove, handler]() { handler(foundMove); });
    };

    getStrand()->post(getMoveAsync);
}

void AsyncAiPlayer::asyncShowMove(const ChessBoard& board, Move& move, AsyncPlayer::ReadyHandler handler)
{
    auto showMoveAsync = [this, &board, &move, handler]()
    {
        showMove(board, move);
        getStrand()->post([handler]() { handler(); });
    };

    getStrand()->post(showMoveAsync);
}

void AsyncAiPlayer::asyncShowResult(const ChessBoard& board, AsyncPlayer::EndStatus status, AsyncPlayer::ReadyHandler handler)
{
    handler();
}

void AsyncAiPlayer::cancel()
{

}

AsyncPlayer::EndStatus AsyncAiPlayer::getStatus(ChessBoard& board)
{
    ChessPlayer::Status status;
    int color = AsyncPlayer::getColor();

    status = board.getPlayerStatus(color);

    if (status == ChessPlayer::Normal || status == ChessPlayer::InCheck)
    {
        return AsyncPlayer::NONE;
    }
    else if (status == ChessPlayer::Checkmate && color == WHITE )
    {
        return AsyncPlayer::WHITE_LOOSE;
    }
    else if (status == ChessPlayer::Stalemate && color == WHITE )
    {
        return AsyncPlayer::WHITE_LOOSE;
    }
    else if (status == ChessPlayer::Stalemate && color == BLACK )
    {
        return AsyncPlayer::WHITE_WIN;
    }
    else if (status == ChessPlayer::Checkmate && color == BLACK )
    {
        return AsyncPlayer::WHITE_WIN;
    }

    return AsyncPlayer::NONE;
}
