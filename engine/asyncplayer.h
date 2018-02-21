#pragma once
#include "chessplayer.h"

#include <boost/asio/io_service.hpp>
#include <functional>

class AsyncPlayer /*: public ChessPlayer*/
{
public:
    enum EndStatus {
        NONE = 0,
        WHITE_WIN,
        DRAW,
        WHITE_LOOSE
    };

    typedef std::function <void (const Move&) > MoveReadyHandler;
    typedef std::function <void (EndStatus) > ResultReadyHandler;
    typedef std::function <void()> ReadyHandler;

    AsyncPlayer(int color);
    virtual ~AsyncPlayer();

    virtual void asyncPrepare(const ChessBoard & board, ReadyHandler handler) = 0;
    virtual void asyncGetMove(const ChessBoard & board, MoveReadyHandler handler) = 0;
    virtual void asyncShowMove(const ChessBoard & board, Move & move, ReadyHandler handler) = 0;
    virtual void asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler) = 0;

    /**
     * @brief cancel -- cancels any of the asunc operation
     */
    virtual void cancel() = 0;

    int getColor() const;
    void setColor(int color);

    std::shared_ptr<boost::asio::io_service::strand> getStrand() const;
    void setStrand(const std::shared_ptr<boost::asio::io_service::strand>& strand);

    std::shared_ptr<boost::asio::io_service> getIoService() const;
    void setIoService(const std::shared_ptr<boost::asio::io_service>& ioService);

private:
    int color_;
    std::shared_ptr<boost::asio::io_service::strand> strand_;
    std::shared_ptr<boost::asio::io_service> ioService_;
};

typedef std::shared_ptr<AsyncPlayer> TAsyncPlayerPtr;
