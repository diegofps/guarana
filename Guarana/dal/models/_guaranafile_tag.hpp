#ifndef GUARANAFILE_TAG_HPP
#define GUARANAFILE_TAG_HPP

class _GuaranaFile_Tag
{
private:

    long _id;

    long _guaranaFileId;

    long _tagId;

public:

    _GuaranaFile_Tag()
    {

    }

    _GuaranaFile_Tag(long guaranaFileId, long tagId) :
        _guaranaFileId(guaranaFileId),
        _tagId(tagId)
    {

    }

    long getGuaranaFileId() const
    {
        return _guaranaFileId;
    }

    long getTagId() const
    {
        return _tagId;
    }

    void setGuaranaFileId(const long guaranaFileId)
    {
        _guaranaFileId = guaranaFileId;
    }

    void setTagId(const long tagId)
    {
        _tagId = tagId;
    }

};

#endif // GUARANAFILE_TAG_HPP
