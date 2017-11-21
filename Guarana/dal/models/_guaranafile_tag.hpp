#ifndef GUARANAFILE_TAG_HPP
#define GUARANAFILE_TAG_HPP

class _GuaranaFile_Tag
{
private:

    int _id;

    int _guaranaFileId;

    int _tagId;

public:

    _GuaranaFile_Tag() : _id(0)
    {

    }

    _GuaranaFile_Tag(int guaranaFileId, int tagId) :
        _id(0),
        _guaranaFileId(guaranaFileId),
        _tagId(tagId)
    {

    }

    int getId() const
    {
        return _id;
    }

    int getGuaranaFileId() const
    {
        return _guaranaFileId;
    }

    int getTagId() const
    {
        return _tagId;
    }

    void setId(int id)
    {
        _id = id;
    }

    void setGuaranaFileId(const int guaranaFileId)
    {
        _guaranaFileId = guaranaFileId;
    }

    void setTagId(const int tagId)
    {
        _tagId = tagId;
    }

};

#endif // GUARANAFILE_TAG_HPP
