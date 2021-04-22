

namespace BassMovement
{
    static int BodyDirection;
    static int BodySpeed;

    static bool IsFlappingTail;


    static long MouthThen;
    static long BodyThen;
    static long LastTalked;


    static int MinSeen,MaxSeen;

    void FlapTail(int Times, int Duration);    
    void OpenMouth();
    void CloseMouth();
    void MoveBody(bool IsTalking);
};