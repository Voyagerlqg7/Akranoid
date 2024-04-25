#pragma once
#include <QPoint>
#include <QImage>

class Item {
public:
	Item():
	m_image(QImage()),
	m_cords(QPoint())
	{}
	QPoint getCords() { return m_cords; }
	void setCords(QPoint cords) { m_cords = cords; }
	QImage& getImage() { return m_image; }
	void setImage(const QImage& image) { m_image = image; }
private:
	QPoint m_cords;
	QImage m_image;
};