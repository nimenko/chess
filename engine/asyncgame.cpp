#include <memory>

#include <boost/bind.hpp>

#include "asyncgame.h"

AsyncGame::AsyncGame(std::shared_ptr<boost::asio::io_service> ioService,
                     std::shared_ptr<AsyncAiPlayer> player1,
                     std::shared_ptr<AsyncAiPlayer> player2) :
    ioService_(ioService),
    player1_(player1),
    player2_(player2),
    gameStatus_(AsyncPlayer::EndStatus::NONE)
{
    strand_ = std::make_shared<boost::asio::io_service::strand>(*ioService);

    board_.initDefaultSetup();

    player1_->setIoService(ioService_);
    player2_->setIoService(ioService_);

    player1_->setStrand(strand_);
    player2_->setStrand(strand_);
}

void AsyncGame::start(AsyncPlayer::ResultReadyHandler resultReadyHandler)
{
    resultReadyHandler_ = resultReadyHandler;

    player1_->asyncPrepare(board_, [](){});
    player2_->asyncPrepare(board_, [](){});

    player1_->asyncGetMove(board_, boost::bind(&AsyncGame::onGetMove, this, _1));
}

void AsyncGame::onGetMove(const Move& move)
{
    move_ = move;
    board_.move(move_);
    player2_->asyncShowMove(board_, move_, boost::bind(&AsyncGame::onShowMove, this));
}

void AsyncGame::onShowMove()
{
    board_.print(move_);
    std::cout << board_.toFEN() << std::endl;
    
    gameStatus_ = player2_->getStatus(board_);
    if (gameStatus_ != AsyncPlayer::NONE)
    {
        resultReadyHandler_(gameStatus_);
    }
    else
    {
        std::swap(player1_, player2_);
        player1_->asyncGetMove(board_, boost::bind(&AsyncGame::onGetMove, this, _1));
    }
}
