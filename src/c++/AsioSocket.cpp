#include "include/AsioSocket.hpp"

namespace educhat {

	AsioSocket::AsioSocket()
		: socket(io_service)
	{
		reset();
		send_in_progress = false;
		recv_in_progress = false;
		recv_msg[0] = '\0';
		recv_msg[RECVMSG_MAXLENGTH-1] = '\0';
		t = nullptr;
	}

	void AsioSocket::reset()
	{
		socket = boost::asio::ip::tcp::socket(io_service);
		connected = false;
		connect_in_progress = false;
	}

	AsioSocket::~AsioSocket()
	{
		io_service.post([this]() { socket.close(); });
		t->join();
		delete t;
	}

	void AsioSocket::connect(const std::string addr, const std::string port)
	{
		if (connect_in_progress || connected)
			return;

		connect_in_progress = true;

		boost::asio::ip::tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ addr, port });

		boost::asio::async_connect(socket, endpoint_iterator,
			[this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator)
			{
				connect_in_progress = false;
				if (!ec) {
					connected = true;
					doRecv();
				} else {
					exit(1);
				}
			});

		if (t == nullptr) {
			t = new std::thread([this](){ io_service.run(); });
		}
	}

	bool AsioSocket::isConnected() const
	{
		return connected;
	}

	void AsioSocket::send(const std::string msg)
	{
		if (!msg.empty()) {
			{
				std::lock_guard<std::mutex> lock(to_send_m); // TODO don't like this.... might need to return error on a failed try_lock() instead.
				to_send.push_back(msg);
			}
			doSend();
		}
	}


	void AsioSocket::doSend()
	{
		if (send_in_progress) {
			return;
		}

		std::lock_guard<std::mutex> lock(to_send_m); // TODO: remove and introduce a try_lock() and way to show failure to caller

		if (!to_send.empty()) {
			send_in_progress = true;
	
			boost::asio::async_write(socket,
				boost::asio::buffer(to_send.front().c_str(),
					to_send.front().length()),
				[this](boost::system::error_code ec, std::size_t)
				{
					if (!ec) {
						{
							std::lock_guard<std::mutex> lock(to_send_m);
							to_send.pop_front();
						}
						send_in_progress = false;

						doSend();

					} else {
						socket.close();
						exit(1);
					}
				});
		}
	}

	std::string AsioSocket::recv()
	{
		// TODO: introduce error when can't receive
		std::string msg = "";

		if (to_recv_m.try_lock()) {
		       	if(!to_recv.empty()) {
				msg = to_recv.front();
				to_recv.pop_front();
			}
			to_recv_m.unlock();
		}

		return msg;
	}

	void AsioSocket::doRecv()
	{
		if (recv_in_progress) {
			return;
		}

		recv_in_progress = true;

		socket.async_read_some(//socket,
			boost::asio::buffer(recv_msg, RECVMSG_MAXLENGTH-1),
			[this](boost::system::error_code ec, std::size_t len)
			{
				if (!ec) {
					if (len > 0) {
						for (std::size_t i = len; i < RECVMSG_MAXLENGTH; ++i) {
							recv_msg[i] = '\0';
						}
	
						std::lock_guard<std::mutex> lock(to_recv_m);
						to_recv.push_back(recv_msg);
					}
					
					recv_in_progress = false;
					doRecv();
				} else {
					socket.close();
					exit(1);
				}
			});

	}

} // namespace educhat
