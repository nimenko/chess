#ifndef ASYNC_AI_PLAYER_H_INCLUDED
#define ASYNC_AI_PLAYER_H_INCLUDED

#include "aiplayer.h"
#include "asyncplayer.h"

class AsyncAiPlayer : public AsyncPlayer, public AIPlayer
{
public:
    AsyncAiPlayer(int color, int search_depth);

    void asyncPrepare(const ChessBoard & board, ReadyHandler handler) override;
    void asyncGetMove(const ChessBoard & board, MoveReadyHandler handler) override;
    void asyncShowMove(const ChessBoard & board, Move& move, ReadyHandler handler) override;
    void asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler) override;

    void cancel() override;

    AsyncPlayer::EndStatus getStatus(ChessBoard& board);
};

#endif
