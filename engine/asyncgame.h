#ifndef ASYNC_GAME_H_INCLUDED
#define ASYNC_GAME_H_INCLUDED

#include <functional>

#include <boost/asio.hpp>

#include "asyncaiplayer.h"
#include "chessboard.h"

class AsyncGame
{
public:
    AsyncGame(std::shared_ptr<boost::asio::io_service> ioService,
              std::shared_ptr<AsyncAiPlayer> player1,
              std::shared_ptr<AsyncAiPlayer> player2);

    void start(AsyncPlayer::ResultReadyHandler resultReadyHandler);

private:
    void onGetMove(const Move& move);
    void onShowMove();

    std::shared_ptr<boost::asio::io_service> ioService_;
    std::shared_ptr<boost::asio::io_service::strand> strand_;
    std::shared_ptr<AsyncAiPlayer> player1_;
    std::shared_ptr<AsyncAiPlayer> player2_;

    ChessBoard board_;
    Move move_;
    AsyncPlayer::EndStatus gameStatus_;
    AsyncPlayer::ResultReadyHandler resultReadyHandler_;
};

#endif
