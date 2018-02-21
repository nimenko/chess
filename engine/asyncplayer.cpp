#include "asyncplayer.h"

AsyncPlayer::AsyncPlayer(int color):
    color_(color)
{
}

AsyncPlayer::~AsyncPlayer()
{
}

int AsyncPlayer::getColor() const
{
    return color_;
}

void AsyncPlayer::setColor(int color)
{
    color_ = color;
}

std::shared_ptr<boost::asio::io_service::strand> AsyncPlayer::getStrand() const
{
    return strand_;
}

void AsyncPlayer::setStrand(const std::shared_ptr<boost::asio::io_service::strand>& strand)
{
    strand_ = strand;
}

std::shared_ptr<boost::asio::io_service> AsyncPlayer::getIoService() const
{
    return ioService_;
}

void AsyncPlayer::setIoService(const std::shared_ptr<boost::asio::io_service>& ioService)
{
    ioService_ = ioService;
}
