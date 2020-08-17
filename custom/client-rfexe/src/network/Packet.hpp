#pragma once
#include <assert.h>
#include <stdint.h>
#include <type_traits> // std::is_empty<>
#if defined(_MSC_VER) && _MSC_VER == 1500 // vs2008 compat
namespace std { using std::tr1::is_empty; }
#endif


/// RO packet container.
class Packet
{
public:
	explicit Packet(size_t size) : m_size(size) { }

	short type() const { return *(short*)m_data; }
	size_t size() const { return m_size; }

	const uint8_t* data() const { return m_data; }
	uint8_t* data() { return m_data; }

protected:
	const size_t m_size;
	uint8_t m_data[];
};


/// Typed RO packet manipulator.
template<typename T, typename E = BYTE> class TPacket
{
public:
	/// Constructor that uses an existing packet.
	explicit TPacket(Packet* p)
	{
		m_packet = p;
		assert( vsize() % sizeof(E) == 0 );
	}

	/// Constructor that creates a packet.
	explicit TPacket(size_t count = 0)
	{
		size_t size = bsize() + count * sizeof(E);
		uint8_t* p = new uint8_t[sizeof(Packet) + size];
		m_packet = new(p) Packet(size); // in-place
	}

	// Direct access to the contained packet.
	operator Packet*()
	{
		return m_packet;
	}

	// Byte-level access to the internal packet buffer.
	uint8_t& operator [](int pos)
	{
		return m_packet->data()[pos];
	}

	// Typed access to the internal packet buffer.
	T* operator ->()
	{
		return reinterpret_cast<T*>(m_packet->data());
	}

	/// Total length of the packet.
	size_t size() const
	{
		return m_packet->size();
	};

	/// Number of elements in the variable-length part of the packet.
	size_t count() const
	{
		return vsize() / sizeof(E);
	}

private:
	/// Size of the fixed-size part of the packet.
	size_t bsize() const
	{
		return ( !std::is_empty<T>::value ) ? sizeof(T) : 0;
	}

	/// Size of the variable-length part of the packet.
	size_t vsize() const
	{
		return size() - bsize();
	}

private:
	Packet* m_packet;
};
