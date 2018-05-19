#pragma once

struct D3D11_BUFFER_DESC;
struct D3D11_SUBRESOURCE_DATA;
class ID3D11Buffer;


class BufferCreator {
    static void createBuffer(const void* data, int size, D3D11_BUFFER_DESC bDesc, D3D11_SUBRESOURCE_DATA srDesc, ID3D11Buffer* buffer)
    {

    }
};