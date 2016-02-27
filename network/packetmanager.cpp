#include "packetmanager.h"
#include "packet.h"

void __private_addPacket(Packet** list, Packet* packet){
    list[packet->getId()] = packet;
}

PacketManager::PacketManager()
{

}

Packet *PacketManager::clientPacket(quint8 id)
{
    return _packet[id + 0x100];
}

Packet *PacketManager::serverPacket(quint8 id)
{
    return _packet[id];
}

Packet *PacketManager::getClientPacket(quint8 id)
{
    return PacketManager::clientPacket(id);
}

Packet *PacketManager::getServerPacket(quint8 id)
{
    return PacketManager::serverPacket(id);
}

Packet** PacketManager::_packet = PacketManager::initPacket();

Packet **PacketManager::initPacket()
{
    /** Contains paquet information for :
     *  Server -write-> Network -read-> Client
     *
     * It's included for a client to read the packet from the server
     * and the server to write packet to the client
     */
    Packet** packet = new Packet*[0x200];

    for(int i=0; i<0x200; i++){
        packet[i] = NULL;
    }

    // Common packet argument
    // int16 is often card id
    // int32 is often player id
    QVector<int> arg_1int16(1, Packet::int16);
    QVector<int> arg_1int32(1, Packet::int32);

    QVector<int> arg_array_int16(1, Packet::array|Packet::int32);

    QVector<int> arg_1str(1, Packet::string);
    QVector<int> arg_2str(2, Packet::string);

    QVector<int> arg_player_str(2, Packet::int32);
    arg_player_str[1] = Packet::string;

    QVector<int> arg_player_int16(2, Packet::int32);
    arg_player_int16[1] = Packet::int16;

    // Packet specific argument
    QVector<int> arg_packet_11(6, Packet::int8);
    arg_packet_11[0] = Packet::int16;
    arg_packet_11[4] = Packet::string;
    arg_packet_11[5] = Packet::string;

    QVector<int> arg_packet_30(6, Packet::int8);
    arg_packet_30[0] = Packet::int32;

    QVector<int> arg_packet_31(2, Packet::int8);
    arg_packet_30[0] = Packet::int32;

    QVector<int> arg_packet_creature_stats(3, Packet::int8);
    arg_packet_30[0] = Packet::int32;

    // Register Server Packet
    __private_addPacket(packet, new Packet(0x01, arg_2str));                     // Message
    __private_addPacket(packet, new Packet(0x02, arg_1str));                     // Information
    __private_addPacket(packet, new Packet(0x0F, arg_1int32));                   // Start signal

    __private_addPacket(packet, new Packet(0x10, arg_array_int16));              // Add Card
    __private_addPacket(packet, new Packet(0x11, arg_1int16));                   // Card Info
    __private_addPacket(packet, new Packet(0x18, arg_1int16));                   // Enable Card
    __private_addPacket(packet, new Packet(0x19, arg_1int16));                   // Disable Card

    __private_addPacket(packet, new Packet(0x20, arg_player_str));               // Rename
    __private_addPacket(packet, new Packet(0x21, arg_1int32));                   // Player Ready
    __private_addPacket(packet, new Packet(0x22, arg_1int32));                   // Player Unprepared
    __private_addPacket(packet, new Packet(0x28, arg_player_int16));             // Player Mana
    __private_addPacket(packet, new Packet(0x29, arg_player_int16));             // Player Energy

    __private_addPacket(packet, new Packet(0x30, arg_packet_30));                // Creature
    __private_addPacket(packet, new Packet(0x31, arg_packet_31));                // Remove Creature
    __private_addPacket(packet, new Packet(0x38, arg_packet_creature_stats));    // Creature set Damage
    __private_addPacket(packet, new Packet(0x39, arg_packet_creature_stats));    // Set Hp

    // Register Client Packet
    __private_addPacket(packet, new Packet(0x101, arg_1str));                    // Message

    __private_addPacket(packet, new Packet(0x120, arg_1str));                    // Rename

    return packet;
}
