#ifndef __BUILDING_H__
#define __BUILDING_H__

template<class T>
class Building_t
{
public:
    Building_t(const T& _id);
    virtual ~Building_t();
    const T SetBuildingID(const T& _id);
    const T& GetBuildingID() const;
private:
    T m_id;
    Building_t(const Building_t& _buiding);
    Building_t& operator=(const Building_t& _building);
};

template<class T>
Building_t<T>::Building_t(const T& _id)
{
    m_id = _id;
}

template<class T>
Building_t<T>::~Building_t()
{

}

template<class T>
const T Building_t<T>::SetBuildingID(const T& _id)
{
    T oldId = m_id;
    m_id = _id;
    return oldId;
}

template<class T>
const T& Building_t<T>::GetBuildingID() const
{
    return m_id;
}

#endif/* __BUILDING_H__*/