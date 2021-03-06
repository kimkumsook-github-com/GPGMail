#import <Cocoa/Cocoa.h>

#ifdef SNOW_LEOPARD_64

#import <SafeObserver.h>

@class MailboxUid;
@class MailAccount;
@class ObjectCache;
@class ActivityMonitor;

@interface MessageStore : SafeObserver
{
    BOOL _isReadOnly;
    BOOL _hasUnsavedChangesToMessageData;
    BOOL _haveOpenLockFile;
    BOOL _forceInvalidation;
    BOOL _isWritingChangesToDisk;
    BOOL _isTryingToClose;
    BOOL _compactOnClose;
    MailboxUid *_mailboxUid;
    MailAccount *_account;
    NSMutableArray *_allMessages;
    id _messageCountsAndSizesLock;
    struct {
        unsigned long long unreadCount;
        unsigned long long unseenCount;
        unsigned long long deletedCount;
        unsigned long long totalSize;
        unsigned long long deletedSize;
    } _messageCountsAndSizes;
    id _cacheLock;
    NSCache *_headerDataCache;
    NSCache *_headerCache;
    NSCache *_bodyDataCache;
    NSCache *_bodyCache;
    NSMutableSet *_uniqueStrings;
    int _storeState;
    NSTimer *_timer;
    ActivityMonitor *_openMonitor;
    NSMutableDictionary *_fetchLockMap;
}

+ (void)initialize;
+ (id)_storeCacheMapTable;
+ (unsigned long long)numberOfCurrentlyOpenStores;
+ (id)descriptionOfOpenStores;
+ (id)_storeCreationMarker;
+ (id)_copyRawAvailableStoreForUid:(id)arg1 wantsCreate:(BOOL)arg2 shouldCreate:(char *)arg3;
+ (id)currentlyAvailableStoreForUid:(id)arg1;
+ (id)currentlyAvailableStoresForAccount:(id)arg1;
+ (void)registerAvailableStore:(id)arg1 forUid:(id)arg2;
+ (void)removeStoreFromCache:(id)arg1;
+ (BOOL)createEmptyStoreIfNeededForPath:(id)arg1 notIndexable:(BOOL)arg2;
+ (BOOL)createEmptyStoreForPath:(id)arg1;
+ (BOOL)storeAtPathIsWritable:(id)arg1;
+ (BOOL)cheapStoreAtPathIsEmpty:(id)arg1;
+ (id)succesfulMessagesFromMessages:(id)arg1 unsuccessfulOnes:(id)arg2;
+ (int)copyMessages:(id)arg1 toMailboxUid:(id)arg2 shouldDelete:(BOOL)arg3;
- (void)queueSaveChangesInvocation;
- (id)willDealloc;
- (id)init;
- (id)initWithMailboxUid:(id)arg1 readOnly:(BOOL)arg2;
- (void)_messageStoreCommonInit;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (void)dealloc;
- (void)finalize;
- (void)openAsynchronously;
- (void)openAsynchronouslyWithOptions:(unsigned int)arg1;
- (void)openSynchronously;
- (void)openSynchronouslyUpdatingMetadata:(BOOL)arg1;
- (void)updateMetadataAsynchronously;
- (void)updateMetadata;
- (void)cleanupAsynchronously;
- (void)cleanupSynchronously;
- (void)willOpen;
- (void)didOpenWithMessages:(id)arg1;
- (void)cancelOpen;
- (void)writeUpdatedMessageDataToDisk;
- (void)invalidateSavingChanges:(BOOL)arg1;
- (id)account;
- (id)mailboxUid;
- (id)allMailboxUidRepresentations;
- (BOOL)isOpened;
- (id)displayName;
- (const char *)displayNameForLogging;
- (id)description;
- (BOOL)isTrash;
- (void)messageFlagsDidChange:(id)arg1 flags:(id)arg2;
- (void)structureDidChange;
- (void)messagesWereAdded:(id)arg1;
- (void)messagesWereCompacted:(id)arg1;
- (void)messagesWereUpdated:(id)arg1;
- (void)updateUserInfoToLatestValues;
- (unsigned long long)totalMessageSize;
- (void)deletedCount:(unsigned long long *)arg1 andSize:(unsigned long long *)arg2;
- (unsigned long long)totalCount;
- (unsigned long long)_totalNonDeletedCount;
- (unsigned long long)unreadCount;
- (unsigned long long)unseenCount;
- (unsigned long long)indexOfMessage:(id)arg1;
- (id)copyOfAllMessages;
- (id)mutableCopyOfAllMessages;
- (id)copyOfAllMessagesWithOptions:(unsigned int)arg1;
- (void)addMessagesToAllMessages:(id)arg1;
- (id)_defaultRouterDestination;
- (id)routeMessages:(id)arg1;
- (id)finishRoutingMessages:(id)arg1 routed:(id)arg2;
- (id)routeMessages:(id)arg1 isUserAction:(BOOL)arg2;
- (BOOL)canRebuild;
- (void)rebuildTableOfContentsAsynchronously;
- (BOOL)canCompact;
- (void)doCompact;
- (void)deleteMessagesOlderThanNumberOfDays:(long long)arg1 compact:(BOOL)arg2;
- (void)deleteMessages:(id)arg1 moveToTrash:(BOOL)arg2;
- (id)undeleteMessages:(id)arg1 movedToStore:(id)arg2 newMessageIDs:(id)arg3;
- (void)undeleteMessages:(id)arg1;
- (void)deleteLastMessageWithHeaders:(id)arg1 compactWhenDone:(BOOL)arg2;
- (BOOL)allowsAppend;
- (BOOL)allowsOverwrite;
- (BOOL)allowsDeleteInPlace;
- (int)undoAppendOfMessageIDs:(id)arg1;
- (void)finishCopyOfMessages:(id)arg1 fromStore:(id)arg2 originalsWereDeleted:(BOOL)arg3;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 newDocumentIDsByOld:(id)arg5 flagsToSet:(id)arg6 forMove:(BOOL)arg7 error:(id *)arg8;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 flagsToSet:(id)arg5 forMove:(BOOL)arg6 error:(id *)arg7;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 flagsToSet:(id)arg5 forMove:(BOOL)arg6;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 flagsToSet:(id)arg5;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 forMove:(BOOL)arg5;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2;
- (id)messageWithValue:(id)arg1 forHeader:(id)arg2 options:(unsigned long long)arg3;
- (id)messageForMessageID:(id)arg1;
- (unsigned long long)_numberOfMessagesToCache;
- (id)headerDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)headerDataForMessage:(id)arg1;
- (id)bodyDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)bodyDataForMessage:(id)arg1;
- (id)fullBodyDataForMessage:(id)arg1 andHeaderDataIfReadilyAvailable:(id *)arg2 fetchIfNotAvailable:(BOOL)arg3;
- (id)fullBodyDataForMessage:(id)arg1 andHeaderDataIfReadilyAvailable:(id *)arg2;
- (id)fullBodyDataForMessage:(id)arg1;
- (id)bodyForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)bodyForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2 updateFlags:(BOOL)arg3;
- (id)headersForMessage:(id)arg1;
- (id)headersForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)dataForMimePart:(id)arg1;
- (BOOL)hasCachedDataForMimePart:(id)arg1;
- (id)uniquedString:(id)arg1;
- (id)colorForMessage:(id)arg1;
- (id)setFlagsFromDictionary:(id)arg1 forMessages:(id)arg2;
- (id)setFlagsFromDictionary:(id)arg1 forToDos:(id)arg2;
- (void)setFlag:(id)arg1 state:(BOOL)arg2 forMessages:(id)arg3;
- (void)setColor:(id)arg1 highlightTextOnly:(BOOL)arg2 forMessages:(id)arg3;
- (void)messageColorsNeedToBeReevaluated;
- (void)startSynchronization;
- (id)_getSerialNumberString;
- (void)setNumberOfAttachments:(unsigned int)arg1 isSigned:(BOOL)arg2 isEncrypted:(BOOL)arg3 forMessage:(id)arg4;
- (void)updateNumberOfAttachmentsForMessages:(id)arg1;
- (void)updateNumberOfAttachmentsAndColorsForMessages:(id)arg1;
- (void)updateMessageColorsSynchronouslyForMessages:(id)arg1;
- (void)updateMessageColorsAsynchronouslyForMessages:(id)arg1;
- (void)setJunkMailLevel:(int)arg1 forMessages:(id)arg2;
- (void)setJunkMailLevel:(int)arg1 forMessages:(id)arg2 trainJunkMailDatabase:(BOOL)arg3;
- (void)setJunkMailLevel:(int)arg1 forMessages:(id)arg2 trainJunkMailDatabase:(BOOL)arg3 userRecorded:(BOOL)arg4;
- (void)sendResponseType:(BOOL)arg1 forMeetingMessage:(id)arg2;
- (id)status;
- (void)fetchSynchronously;
- (void)fetchSynchronouslyForKnownChanges;
- (BOOL)setPreferredEncoding:(unsigned int)arg1 forMessage:(id)arg2;
- (void)suggestSortOrder:(id)arg1 ascending:(BOOL)arg2;
- (id)sortOrder;
- (BOOL)isSortedAscending;
- (void)todosDidChangeForMessages:(id)arg1 oldToDosByMessage:(id)arg2 newToDosByMessage:(id)arg3;
- (int)setToDo:(id)arg1 forMessage:(id)arg2 oldToDo:(id)arg3;
- (void)invalidateMessage:(id)arg1;
- (void)invalidateMessages:(id)arg1;
- (id)_aquireFetchLockForMessage:(id)arg1;
- (void)_releaseFetchLock:(id)arg1 forMessage:(id)arg2;
@property BOOL forceInvalidation; // @synthesize forceInvalidation=_forceInvalidation;
@property BOOL hasUnsavedChangesToMessageData; // @synthesize hasUnsavedChangesToMessageData=_hasUnsavedChangesToMessageData;
@property(retain) ActivityMonitor *openMonitor; // @synthesize openMonitor=_openMonitor;
@property BOOL isReadOnly; // @synthesize isReadOnly=_isReadOnly;

@end

@interface MessageStore (MessageFrameworkOnly)
+ (void)_autosaveMessageStore:(void *)arg1;
- (void)_cancelAutosave;
- (void)_setNeedsAutosave;
- (id)_fetchHeaderDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)_fetchBodyDataForMessage:(id)arg1 andHeaderDataIfReadilyAvailable:(id *)arg2 fetchIfNotAvailable:(BOOL)arg3;
- (id)_fetchBodyForMessage:(id)arg1 updateFlags:(BOOL)arg2;
- (BOOL)_shouldCallCompactWhenClosing;
- (BOOL)_isReadyToBeInvalidated;
- (void)_saveChanges;
- (BOOL)setStoreState:(int)arg1 fromState:(int)arg2;
- (int)storeState;
- (void)_invalidate;
- (void)_invalidateInBackground;
- (void)_countUnreadAndDeletedInMessages:(id)arg1;
- (id)_lockFilePath;
- (BOOL)_acquireLockFile;
- (void)_removeLockFile;
- (void)_flushAllCaches;
- (void)_flushAllMessageData;
- (void)_rebuildTableOfContentsSynchronously;
- (void)updateBodyFlagsForMessage:(id)arg1 body:(id)arg2;
- (id)_setOrGetBody:(id)arg1 forMessage:(id)arg2 updateFlags:(BOOL)arg3;
- (void)_invalidateObjectCachesForKey:(id)arg1;
- (id)_setOrGetValue:(id)arg1 forKey:(id)arg2 inCache:(id *)arg3;
- (id)_cachedBodyForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (id)_cachedHeadersForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (id)_cachedBodyDataForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (id)_cachedHeaderDataForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (void)updateMessageColorsSynchronouslyForMessages:(id)arg1 postingNotification:(BOOL)arg2;
- (void)updateMessages:(id)arg1 updateColor:(BOOL)arg2 updateNumberOfAttachments:(BOOL)arg3;
- (void)_setBackgroundColorForMessages:(id)arg1 textColorForMessages:(id)arg2;
- (void)_invalidateColorForAllMessages;
- (void)_setFlagsForMessages:(id)arg1 mask:(unsigned int)arg2;
- (void)_setFlagsAndColorForMessages:(id)arg1;
- (void)messagesWereAdded:(id)arg1 forIncrementalLoading:(BOOL)arg2;
- (BOOL)_updateFlagForMessage:(id)arg1 key:(id)arg2 value:(BOOL)arg3;

// Remaining properties
@property BOOL forceInvalidation;
@property BOOL hasUnsavedChangesToMessageData;
@property BOOL isReadOnly;
@end

@interface MessageStore (ParentalControl)
- (void)setPermissionRequestState:(int)arg1 forMessage:(id)arg2;
@end

@interface MessageStore (RSSAdditions)
+ (void)deleteUnflaggedEntriesCreatedBeforeDate:(id)arg1;
- (void)updateEntries:(id)arg1 fromFeed:(id)arg2;
- (void)changeFlagsForEntries:(id)arg1 fromFeed:(id)arg2;
- (void)updateStatusFromFeed:(id)arg1 error:(id)arg2 errorMessage:(id)arg3;
@end

@interface MessageStore (ScriptingSupport)
- (id)objectSpecifier;
- (id)objectSpecifierForMessage:(id)arg1;
@end



#elif defined(SNOW_LEOPARD)

#import <SafeObserver.h>

@class MailboxUid;
@class MailAccount;
@class NSCache;
@class ActivityMonitor;

@interface MessageStore : SafeObserver
{
    BOOL _isReadOnly;
    BOOL _hasUnsavedChangesToMessageData;
    BOOL _haveOpenLockFile;
    BOOL _forceInvalidation;
    BOOL _isWritingChangesToDisk;
    BOOL _isTryingToClose;
    BOOL _compactOnClose;
    MailboxUid *_mailboxUid;
    MailAccount *_account;
    NSMutableArray *_allMessages;
    id _messageCountsAndSizesLock;
    struct {
        unsigned int unreadCount;
        unsigned int unseenCount;
        unsigned int deletedCount;
        unsigned int totalSize;
        unsigned int deletedSize;
    } _messageCountsAndSizes;
    id _cacheLock;
    NSCache *_headerDataCache;
    NSCache *_headerCache;
    NSCache *_bodyDataCache;
    NSCache *_bodyCache;
    NSMutableSet *_uniqueStrings;
    int _storeState;
    NSTimer *_timer;
    ActivityMonitor *_openMonitor;
    NSMutableDictionary *_fetchLockMap;
}

+ (void)initialize;
+ (id)_storeCacheMapTable;
+ (unsigned int)numberOfCurrentlyOpenStores;
+ (id)descriptionOfOpenStores;
+ (id)_storeCreationMarker;
+ (id)_copyRawAvailableStoreForUid:(id)arg1 wantsCreate:(BOOL)arg2 shouldCreate:(char *)arg3;
+ (id)currentlyAvailableStoreForUid:(id)arg1;
+ (id)currentlyAvailableStoresForAccount:(id)arg1;
+ (void)registerAvailableStore:(id)arg1 forUid:(id)arg2;
+ (void)removeStoreFromCache:(id)arg1;
+ (BOOL)createEmptyStoreIfNeededForPath:(id)arg1 notIndexable:(BOOL)arg2;
+ (BOOL)createEmptyStoreForPath:(id)arg1;
+ (BOOL)storeAtPathIsWritable:(id)arg1;
+ (BOOL)cheapStoreAtPathIsEmpty:(id)arg1;
+ (id)succesfulMessagesFromMessages:(id)arg1 unsuccessfulOnes:(id)arg2;
+ (int)copyMessages:(id)arg1 toMailboxUid:(id)arg2 shouldDelete:(BOOL)arg3;
- (void)queueSaveChangesInvocation;
- (id)willDealloc;
- (id)init;
- (id)initWithMailboxUid:(id)arg1 readOnly:(BOOL)arg2;
- (void)_messageStoreCommonInit;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (void)dealloc;
- (void)finalize;
- (void)openAsynchronously;
- (void)openAsynchronouslyWithOptions:(unsigned int)arg1;
- (void)openSynchronously;
- (void)openSynchronouslyUpdatingMetadata:(BOOL)arg1;
- (void)updateMetadataAsynchronously;
- (void)updateMetadata;
- (void)cleanupAsynchronously;
- (void)cleanupSynchronously;
- (void)willOpen;
- (void)didOpenWithMessages:(id)arg1;
- (void)cancelOpen;
- (void)writeUpdatedMessageDataToDisk;
- (void)invalidateSavingChanges:(BOOL)arg1;
- (id)account;
- (id)mailboxUid;
- (id)allMailboxUidRepresentations;
- (BOOL)isOpened;
- (id)displayName;
- (const char *)displayNameForLogging;
- (id)description;
- (BOOL)isTrash;
- (void)messageFlagsDidChange:(id)arg1 flags:(id)arg2;
- (void)structureDidChange;
- (void)messagesWereAdded:(id)arg1;
- (void)messagesWereCompacted:(id)arg1;
- (void)messagesWereUpdated:(id)arg1;
- (void)updateUserInfoToLatestValues;
- (unsigned int)totalMessageSize;
- (void)deletedCount:(unsigned int *)arg1 andSize:(unsigned int *)arg2;
- (unsigned int)totalCount;
- (unsigned int)_totalNonDeletedCount;
- (unsigned int)unreadCount;
- (unsigned int)unseenCount;
- (unsigned int)indexOfMessage:(id)arg1;
- (id)copyOfAllMessages;
- (id)mutableCopyOfAllMessages;
- (id)copyOfAllMessagesWithOptions:(unsigned int)arg1;
- (void)addMessagesToAllMessages:(id)arg1;
- (id)_defaultRouterDestination;
- (id)routeMessages:(id)arg1;
- (id)finishRoutingMessages:(id)arg1 routed:(id)arg2;
- (id)routeMessages:(id)arg1 isUserAction:(BOOL)arg2;
- (BOOL)canRebuild;
- (void)rebuildTableOfContentsAsynchronously;
- (BOOL)canCompact;
- (void)doCompact;
- (void)deleteMessagesOlderThanNumberOfDays:(int)arg1 compact:(BOOL)arg2;
- (void)deleteMessages:(id)arg1 moveToTrash:(BOOL)arg2;
- (id)undeleteMessages:(id)arg1 movedToStore:(id)arg2 newMessageIDs:(id)arg3;
- (void)undeleteMessages:(id)arg1;
- (void)deleteLastMessageWithHeaders:(id)arg1 compactWhenDone:(BOOL)arg2;
- (BOOL)allowsAppend;
- (BOOL)allowsOverwrite;
- (BOOL)allowsDeleteInPlace;
- (int)undoAppendOfMessageIDs:(id)arg1;
- (void)finishCopyOfMessages:(id)arg1 fromStore:(id)arg2 originalsWereDeleted:(BOOL)arg3;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 newDocumentIDsByOld:(id)arg5 flagsToSet:(id)arg6 forMove:(BOOL)arg7 error:(id *)arg8;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 flagsToSet:(id)arg5 forMove:(BOOL)arg6 error:(id *)arg7;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 flagsToSet:(id)arg5 forMove:(BOOL)arg6;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 flagsToSet:(id)arg5;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4 forMove:(BOOL)arg5;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3 newMessages:(id)arg4;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2 newMessageIDs:(id)arg3;
- (int)appendMessages:(id)arg1 unsuccessfulOnes:(id)arg2;
- (id)messageWithValue:(id)arg1 forHeader:(id)arg2 options:(unsigned int)arg3;
- (id)messageForMessageID:(id)arg1;
- (unsigned int)_numberOfMessagesToCache;
- (id)headerDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)headerDataForMessage:(id)arg1;
- (id)bodyDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)bodyDataForMessage:(id)arg1;
- (id)fullBodyDataForMessage:(id)arg1 andHeaderDataIfReadilyAvailable:(id *)arg2 fetchIfNotAvailable:(BOOL)arg3;
- (id)fullBodyDataForMessage:(id)arg1 andHeaderDataIfReadilyAvailable:(id *)arg2;
- (id)fullBodyDataForMessage:(id)arg1;
- (id)bodyForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)bodyForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2 updateFlags:(BOOL)arg3;
- (id)headersForMessage:(id)arg1;
- (id)headersForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)dataForMimePart:(id)arg1;
- (BOOL)hasCachedDataForMimePart:(id)arg1;
- (id)uniquedString:(id)arg1;
- (id)colorForMessage:(id)arg1;
- (id)setFlagsFromDictionary:(id)arg1 forMessages:(id)arg2;
- (id)setFlagsFromDictionary:(id)arg1 forToDos:(id)arg2;
- (void)setFlag:(id)arg1 state:(BOOL)arg2 forMessages:(id)arg3;
- (void)setColor:(id)arg1 highlightTextOnly:(BOOL)arg2 forMessages:(id)arg3;
- (void)messageColorsNeedToBeReevaluated;
- (void)startSynchronization;
- (id)_getSerialNumberString;
- (void)setNumberOfAttachments:(unsigned long)arg1 isSigned:(BOOL)arg2 isEncrypted:(BOOL)arg3 forMessage:(id)arg4;
- (void)updateNumberOfAttachmentsForMessages:(id)arg1;
- (void)updateNumberOfAttachmentsAndColorsForMessages:(id)arg1;
- (void)updateMessageColorsSynchronouslyForMessages:(id)arg1;
- (void)updateMessageColorsAsynchronouslyForMessages:(id)arg1;
- (void)setJunkMailLevel:(int)arg1 forMessages:(id)arg2;
- (void)setJunkMailLevel:(int)arg1 forMessages:(id)arg2 trainJunkMailDatabase:(BOOL)arg3;
- (void)setJunkMailLevel:(int)arg1 forMessages:(id)arg2 trainJunkMailDatabase:(BOOL)arg3 userRecorded:(BOOL)arg4;
- (void)sendResponseType:(BOOL)arg1 forMeetingMessage:(id)arg2;
- (id)status;
- (void)fetchSynchronously;
- (void)fetchSynchronouslyForKnownChanges;
- (BOOL)setPreferredEncoding:(unsigned long)arg1 forMessage:(id)arg2;
- (void)suggestSortOrder:(id)arg1 ascending:(BOOL)arg2;
- (id)sortOrder;
- (BOOL)isSortedAscending;
- (void)todosDidChangeForMessages:(id)arg1 oldToDosByMessage:(id)arg2 newToDosByMessage:(id)arg3;
- (int)setToDo:(id)arg1 forMessage:(id)arg2 oldToDo:(id)arg3;
- (void)invalidateMessage:(id)arg1;
- (void)invalidateMessages:(id)arg1;
- (id)_aquireFetchLockForMessage:(id)arg1;
- (void)_releaseFetchLock:(id)arg1 forMessage:(id)arg2;
- (BOOL)forceInvalidation;
- (void)setForceInvalidation:(BOOL)arg1;
- (BOOL)hasUnsavedChangesToMessageData;
- (void)setHasUnsavedChangesToMessageData:(BOOL)arg1;
- (id)openMonitor;
- (void)setOpenMonitor:(id)arg1;
- (BOOL)isReadOnly;
- (void)setIsReadOnly:(BOOL)arg1;

@end

@interface MessageStore (MessageFrameworkOnly)
+ (void)_autosaveMessageStore:(void *)arg1;
- (void)_cancelAutosave;
- (void)_setNeedsAutosave;
- (id)_fetchHeaderDataForMessage:(id)arg1 fetchIfNotAvailable:(BOOL)arg2;
- (id)_fetchBodyDataForMessage:(id)arg1 andHeaderDataIfReadilyAvailable:(id *)arg2 fetchIfNotAvailable:(BOOL)arg3;
- (id)_fetchBodyForMessage:(id)arg1 updateFlags:(BOOL)arg2;
- (BOOL)_shouldCallCompactWhenClosing;
- (BOOL)_isReadyToBeInvalidated;
- (void)_saveChanges;
- (BOOL)setStoreState:(int)arg1 fromState:(int)arg2;
- (int)storeState;
- (void)_invalidate;
- (void)_invalidateInBackground;
- (void)_countUnreadAndDeletedInMessages:(id)arg1;
- (id)_lockFilePath;
- (BOOL)_acquireLockFile;
- (void)_removeLockFile;
- (void)_flushAllCaches;
- (void)_flushAllMessageData;
- (void)_rebuildTableOfContentsSynchronously;
- (void)updateBodyFlagsForMessage:(id)arg1 body:(id)arg2;
- (id)_setOrGetBody:(id)arg1 forMessage:(id)arg2 updateFlags:(BOOL)arg3;
- (void)_invalidateObjectCachesForKey:(id)arg1;
- (id)_setOrGetValue:(id)arg1 forKey:(id)arg2 inCache:(id *)arg3;
- (id)_cachedBodyForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (id)_cachedHeadersForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (id)_cachedBodyDataForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (id)_cachedHeaderDataForMessage:(id)arg1 valueIfNotPresent:(id)arg2;
- (void)updateMessageColorsSynchronouslyForMessages:(id)arg1 postingNotification:(BOOL)arg2;
- (void)updateMessages:(id)arg1 updateColor:(BOOL)arg2 updateNumberOfAttachments:(BOOL)arg3;
- (void)_setBackgroundColorForMessages:(id)arg1 textColorForMessages:(id)arg2;
- (void)_invalidateColorForAllMessages;
- (void)_setFlagsForMessages:(id)arg1 mask:(unsigned long)arg2;
- (void)_setFlagsAndColorForMessages:(id)arg1;
- (void)messagesWereAdded:(id)arg1 forIncrementalLoading:(BOOL)arg2;
- (BOOL)_updateFlagForMessage:(id)arg1 key:(id)arg2 value:(BOOL)arg3;
@end

@interface MessageStore (ScriptingSupport)
- (id)objectSpecifier;
- (id)objectSpecifierForMessage:(id)arg1;
@end

@interface MessageStore (ParentalControl)
- (void)setPermissionRequestState:(int)arg1 forMessage:(id)arg2;
@end

@interface MessageStore (RSSAdditions)
+ (void)deleteUnflaggedEntriesCreatedBeforeDate:(id)arg1;
- (void)updateEntries:(id)arg1 fromFeed:(id)arg2;
- (void)changeFlagsForEntries:(id)arg1 fromFeed:(id)arg2;
- (void)updateStatusFromFeed:(id)arg1 error:(id)arg2 errorMessage:(id)arg3;
@end

#elif defined(LEOPARD)

#import <SafeObserver.h>

@class MailboxUid;
@class MailAccount;
@class ObjectCache;
@class ActivityMonitor;

@interface MessageStore : SafeObserver
{
    struct {
        unsigned int isReadOnly:1;
        unsigned int hasUnsavedChangesToMessageData:1;
        unsigned int haveOpenLockFile:1;
        unsigned int rebuildingTOC:1;
        unsigned int compacting:1;
        unsigned int cancelInvalidation:1;
        unsigned int forceInvalidation:1;
        unsigned int isWritingChangesToDisk:1;
        unsigned int isTryingToClose:1;
        unsigned int compactOnClose:1;
        unsigned int isOpenedByUser:1;
        unsigned int reserved:21;
    } _flags;
    MailboxUid *_mailboxUid;
    MailAccount *_account;
    NSMutableArray *_allMessages;
    unsigned int _allMessagesSize;
    unsigned int _deletedMessagesSize;
    unsigned int _deletedMessageCount;
    unsigned int _unreadMessageCount;
    int _state;
    union {
        struct {
            ObjectCache *_headerDataCache;
            ObjectCache *_headerCache;
            ObjectCache *_bodyDataCache;
            ObjectCache *_bodyCache;
        } objectCaches;
        struct {
            struct __CFDictionary *_headerDataCache;
            struct __CFDictionary *_headerCache;
            struct __CFDictionary *_bodyDataCache;
            struct __CFDictionary *_bodyCache;
        } intKeyCaches;
    } _caches;
    NSTimer *_timer;
    NSMutableSet *_uniqueStrings;
    double timeOfLastAutosaveOperation;
    ActivityMonitor *_openMonitor;
}

+ (void)initialize;
+ (id)_storeCacheMapTable;
+ (unsigned int)numberOfCurrentlyOpenStores;
+ (id)descriptionOfOpenStores;
+ (id)currentlyAvailableStoreForUid:(id)fp8;
+ (id)currentlyAvailableStoresForAccount:(id)fp8;
+ (id)registerAvailableStore:(id)fp8;
+ (void)removeStoreFromCache:(id)fp8;
+ (BOOL)createEmptyStoreIfNeededForPath:(id)fp8 notIndexable:(BOOL)fp12;
+ (BOOL)createEmptyStoreForPath:(id)fp8;
+ (BOOL)storeAtPathIsWritable:(id)fp8;
+ (BOOL)cheapStoreAtPathIsEmpty:(id)fp8;
+ (id)succesfulMessagesFromMessages:(id)fp8 unsuccessfulOnes:(id)fp12;
+ (int)copyMessages:(id)fp8 toMailboxUid:(id)fp12 shouldDelete:(BOOL)fp16;
- (void)queueSaveChangesInvocation;
- (id)willDealloc;
- (id)initWithMailboxUid:(id)fp8 readOnly:(BOOL)fp12;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (void)dealloc;
- (void)finalize;
- (void)openAsynchronouslyUpdatingMetadata:(BOOL)fp8;
- (void)openAsynchronously;
- (void)openAsynchronouslyWithOptions:(unsigned int)fp8;
- (void)openSynchronously;
- (void)openSynchronouslyWithoutUserInteraction;
- (void)openSynchronouslyUpdatingMetadata:(BOOL)fp8;
- (void)updateMetadataAsynchronously;
- (void)updateMetadata;
- (void)cleanupAsynchronously;
- (void)cleanupSynchronously;
- (void)didOpen;
- (void)cancelOpen;
- (void)_setOpenMonitor:(id)fp8;
- (void)writeUpdatedMessageDataToDisk;
- (void)invalidateSavingChanges:(BOOL)fp8;
- (id)account;
- (id)mailboxUid;
- (id)allMailboxUidRepresentations;
- (BOOL)isOpened;
- (id)storePathRelativeToAccount;
- (id)displayName;
- (const char *)displayNameForLogging;
- (BOOL)isReadOnly;
- (id)description;
- (BOOL)isTrash;
- (BOOL)isDrafts;
- (void)messageFlagsDidChange:(id)fp8 flags:(id)fp12;
- (void)structureDidChange;
- (void)messagesWereAdded:(id)fp8;
- (void)messagesWereCompacted:(id)fp8;
- (void)messagesWereUpdated:(id)fp8;
- (void)updateUserInfoToLatestValues;
- (unsigned int)totalMessageSize;
- (void)deletedCount:(unsigned int *)fp8 andSize:(unsigned int *)fp12;
- (unsigned int)totalCount;
- (unsigned int)unreadCount;
- (unsigned int)indexOfMessage:(id)fp8;
- (id)copyOfAllMessages;
- (id)mutableCopyOfAllMessages;
- (id)copyOfAllMessagesWithOptions:(unsigned int)fp8;
- (void)addMessagesToAllMessages:(id)fp8;
- (void)addMessageToAllMessages:(id)fp8;
- (void)insertMessageToAllMessages:(id)fp8 atIndex:(unsigned int)fp12;
- (id)_defaultRouterDestination;
- (id)routeMessages:(id)fp8;
- (id)finishRoutingMessages:(id)fp8 routed:(id)fp12;
- (id)routeMessages:(id)fp8 isUserAction:(BOOL)fp12;
- (BOOL)canRebuild;
- (void)rebuildTableOfContentsAsynchronously;
- (BOOL)canCompact;
- (void)doCompact;
- (void)deleteMessagesOlderThanNumberOfDays:(int)fp8 compact:(BOOL)fp12;
- (void)deleteMessages:(id)fp8 moveToTrash:(BOOL)fp12;
- (void)undeleteMessages:(id)fp8;
- (void)deleteLastMessageWithHeaders:(id)fp8 compactWhenDone:(BOOL)fp12;
- (BOOL)allowsAppend;
- (BOOL)allowsOverwrite;
- (BOOL)isALocalStore;
- (int)undoAppendOfMessageIDs:(id)fp8;
- (void)finishCopyOfMessages:(id)fp8 fromStore:(id)fp12 originalsWereDeleted:(BOOL)fp16;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20 newDocumentIDsByOld:(id)fp24 flagsToSet:(id)fp28 forMove:(BOOL)fp32 error:(id *)fp36;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20 flagsToSet:(id)fp24 forMove:(BOOL)fp28 error:(id *)fp32;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20 flagsToSet:(id)fp24 forMove:(BOOL)fp28;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20 flagsToSet:(id)fp24;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20 forMove:(BOOL)fp24;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12;
- (id)messageWithValue:(id)fp8 forHeader:(id)fp12 options:(unsigned int)fp16;
- (id)messageForMessageID:(id)fp8;
- (id)headerDataForMessage:(id)fp8;
- (id)bodyDataForMessage:(id)fp8;
- (id)fullBodyDataForMessage:(id)fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- (id)fullBodyDataForMessage:(id)fp8;
- (id)bodyForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12;
- (id)bodyForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12 updateFlags:(BOOL)fp16;
- (id)headersForMessage:(id)fp8;
- (id)headersForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12;
- (id)dataForMimePart:(id)fp8;
- (BOOL)hasCachedDataForMimePart:(id)fp8;
- (id)uniquedString:(id)fp8;
- (id)colorForMessage:(id)fp8;
- (id)setFlagsFromDictionary:(id)fp8 forMessages:(id)fp12;
- (id)setFlagsFromDictionary:(id)fp8 forToDos:(id)fp12;
- (id)setFlagsFromDictionary:(id)fp8 forMessage:(id)fp12;
- (id)setFlagsFromDictionary:(id)fp8 forToDo:(id)fp12;
- (void)setFlag:(id)fp8 state:(BOOL)fp12 forMessages:(id)fp16;
- (BOOL)hasUnsavedChangesToMessageData;
- (void)setColor:(id)fp8 highlightTextOnly:(BOOL)fp12 forMessages:(id)fp16;
- (void)messageColorsNeedToBeReevaluated;
- (void)startSynchronization;
- (id)_getSerialNumberString;
- (void)setNumberOfAttachments:(unsigned int)fp8 isSigned:(BOOL)fp12 isEncrypted:(BOOL)fp16 forMessage:(id)fp20;
- (void)updateNumberOfAttachmentsForMessages:(id)fp8;
- (void)updateMessageColorsSynchronouslyForMessages:(id)fp8;
- (void)updateMessageColorsAsynchronouslyForMessages:(id)fp8;
- (void)setJunkMailLevel:(int)fp8 forMessages:(id)fp12;
- (void)setJunkMailLevel:(int)fp8 forMessages:(id)fp12 trainJunkMailDatabase:(BOOL)fp16;
- (void)setJunkMailLevel:(int)fp8 forMessages:(id)fp12 trainJunkMailDatabase:(BOOL)fp16 userRecorded:(BOOL)fp20;
- (id)status;
- (void)fetchSynchronously;
- (BOOL)setPreferredEncoding:(unsigned long)fp8 forMessage:(id)fp12;
- (void)suggestSortOrder:(id)fp8 ascending:(BOOL)fp12;
- (id)sortOrder;
- (BOOL)isSortedAscending;
- (void)todosDidChangeForMessages:(id)fp8 oldToDosByMessage:(id)fp12 newToDosByMessage:(id)fp16;
- (int)setToDo:(id)fp8 forMessage:(id)fp12 oldToDo:(id)fp16;
- (void)invalidateMessage:(id)fp8;
- (void)invalidateMessages:(id)fp8;

@end

@interface MessageStore (MessageFrameworkOnly)
+ (void)_autosaveMessageStore:(void *)fp8;
- (void)_cancelAutosave;
- (void)_setNeedsAutosave;
- (id)_fetchHeaderDataForMessage:(id)fp8;
- (id)_fetchBodyDataForMessage:(id)fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- (id)_fetchBodyForMessage:(id)fp8 updateFlags:(BOOL)fp12;
- (id)_fetchBodyForMessage:(id)fp8;
- (BOOL)_shouldCallCompactWhenClosing;
- (void)_compactMessageAtIndex:(unsigned int)fp8;
- (BOOL)_isReadyToBeInvalidated;
- (void)_saveChanges;
- (void)_setState:(int)fp8;
- (void)_invalidate;
- (void)_invalidateInBackground;
- (void)_countUnreadAndDeleted;
- (void)_cleanUpStaleAttachments;
- (id)_lockFilePath;
- (BOOL)_acquireLockFile:(id)fp8;
- (void)_removeLockFile:(id)fp8;
- (void)_flushAllCaches;
- (void)_flushAllMessageData;
- (void)_rebuildTableOfContentsSynchronously;
- (void)updateBodyFlagsForMessage:(id)fp8 body:(id)fp12;
- (id)_setOrGetBody:(id)fp8 forMessage:(id)fp12 updateFlags:(BOOL)fp16;
- (id)_setOrGetBody:(id)fp8 forMessage:(id)fp12;
- (id)_cachedBodyForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedHeadersForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedBodyDataForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedHeaderDataForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (void)updateMessageColorsSynchronouslyForMessages:(id)fp8 postingNotification:(BOOL)fp12;
- (void)updateMessages:(id)fp8 updateColor:(BOOL)fp12 updateNumberOfAttachments:(BOOL)fp16;
- (void)_setBackgroundColorForMessages:(id)fp8 textColorForMessages:(id)fp12;
- (void)_invalidateColorForMessages:(id)fp8;
- (void)_setFlagsForMessages:(id)fp8 mask:(unsigned long)fp12;
- (void)_setFlagsAndColorForMessages:(id)fp8;
- (void)messagesWereAdded:(id)fp8 forIncrementalLoading:(BOOL)fp12;
- (BOOL)_updateFlagForMessage:(id)fp8 key:(id)fp12 value:(BOOL)fp16;
@end

@interface MessageStore (ScriptingSupport)
- (id)objectSpecifier;
- (id)objectSpecifierForMessage:(id)fp8;
@end

@interface MessageStore (ParentalControl)
- (void)setPermissionRequestState:(int)fp8 forMessage:(id)fp12;
@end

@interface MessageStore (RSSAdditions)
+ (void)deleteUnflaggedEntriesCreatedBeforeDate:(id)fp8;
- (void)updateEntries:(id)fp8 fromFeed:(id)fp12;
- (void)changeFlagsForEntries:(id)fp8 fromFeed:(id)fp12;
- (void)updateStatusFromFeed:(id)fp8 error:(id)fp12 errorMessage:(id)fp16;
@end

#elif defined(TIGER)

#import <SafeObserver.h>

@class MailboxUid;
@class MailAccount;
@class MboxIndex;
@class ObjectCache;
@class ActivityMonitor;

@interface MessageStore : SafeObserver
{
    struct {
        unsigned int isReadOnly:1;
        unsigned int hasUnsavedChangesToMessageData:1;
        unsigned int haveOpenLockFile:1;
        unsigned int rebuildingTOC:1;
        unsigned int compacting:1;
        unsigned int cancelInvalidation:1;
        unsigned int forceInvalidation:1;
        unsigned int isWritingChangesToDisk:1;
        unsigned int isTryingToClose:1;
        unsigned int compactOnClose:1;
        unsigned int reserved:22;
    } _flags;
    MailboxUid *_mailboxUid;
    MailAccount *_account;
    NSMutableArray *_allMessages;
    unsigned int _allMessagesSize;
    unsigned int _deletedMessagesSize;
    unsigned int _deletedMessageCount;
    unsigned int _unreadMessageCount;
    int _state;
    union {
        struct {
            ObjectCache *_headerDataCache;
            ObjectCache *_headerCache;
            ObjectCache *_bodyDataCache;
            ObjectCache *_bodyCache;
        } objectCaches;
        struct {
            struct __CFDictionary *_headerDataCache;
            struct __CFDictionary *_headerCache;
            struct __CFDictionary *_bodyDataCache;
            struct __CFDictionary *_bodyCache;
        } intKeyCaches;
    } _caches;
    NSTimer *_timer;
    NSMutableSet *_uniqueStrings;
    double timeOfLastAutosaveOperation;
    ActivityMonitor *_openMonitor;
}

+ (void)initialize;
+ (struct _NSMapTable *)_storeCacheMapTable;
+ (unsigned int)numberOfCurrentlyOpenStores;
+ (id)descriptionOfOpenStores;
+ (id)currentlyAvailableStoreForUid:(id)fp8;
+ (id)currentlyAvailableStoresForAccount:(id)fp8;
+ (id)registerAvailableStore:(id)fp8;
+ (void)removeStoreFromCache:(id)fp8;
+ (BOOL)createEmptyStoreIfNeededForPath:(id)fp8 notIndexable:(BOOL)fp12;
+ (BOOL)createEmptyStoreForPath:(id)fp8;
+ (BOOL)storeAtPathIsWritable:(id)fp8;
+ (BOOL)cheapStoreAtPathIsEmpty:(id)fp8;
+ (int)copyMessages:(id)fp8 toMailboxUid:(id)fp12 shouldDelete:(BOOL)fp16;
- (void)queueSaveChangesInvocation;
- (id)willBeReleased;
- (id)initWithMailboxUid:(id)fp8 readOnly:(BOOL)fp12;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (void)dealloc;
- (void)finalize;
- (void)openAsynchronouslyUpdatingMetadata:(BOOL)fp8;
- (void)openAsynchronously;
- (void)openAsynchronouslyWithOptions:(unsigned int)fp8;
- (void)openSynchronously;
- (void)openSynchronouslyUpdatingMetadata:(BOOL)fp8;
- (void)updateMetadataAsynchronously;
- (void)updateMetadata;
- (void)didOpen;
- (void)cancelOpen;
- (void)writeUpdatedMessageDataToDisk;
- (void)invalidateSavingChanges:(BOOL)fp8;
- (id)account;
- (id)mailboxUid;
- (BOOL)isOpened;
- (id)storePathRelativeToAccount;
- (id)displayName;
- (const char *)displayNameForLogging;
- (BOOL)isReadOnly;
- (id)description;
- (BOOL)isTrash;
- (BOOL)isDrafts;
- (void)messageFlagsDidChange:(id)fp8 flags:(id)fp12;
- (void)structureDidChange;
- (void)messagesWereAdded:(id)fp8;
- (void)messagesWereCompacted:(id)fp8;
- (void)updateUserInfoToLatestValues;
- (unsigned int)totalMessageSize;
- (void)deletedCount:(unsigned int *)fp8 andSize:(unsigned int *)fp12;
- (unsigned int)totalCount;
- (unsigned int)unreadCount;
- (unsigned int)indexOfMessage:(id)fp8;
- (id)copyOfAllMessages;
- (id)mutableCopyOfAllMessages;
- (id)copyOfAllMessagesWithOptions:(unsigned int)fp8;
- (void)addMessagesToAllMessages:(id)fp8;
- (void)addMessageToAllMessages:(id)fp8;
- (void)insertMessageToAllMessages:(id)fp8 atIndex:(unsigned int)fp12;
- (id)_defaultRouterDestination;
- (id)routeMessages:(id)fp8;
- (id)finishRoutingMessages:(id)fp8 routed:(id)fp12;
- (id)routeMessages:(id)fp8 isUserAction:(BOOL)fp12;
- (BOOL)canRebuild;
- (void)rebuildTableOfContentsAsynchronously;
- (BOOL)canCompact;
- (void)doCompact;
- (void)deleteMessagesOlderThanNumberOfDays:(int)fp8 compact:(BOOL)fp12;
- (void)deleteMessages:(id)fp8 moveToTrash:(BOOL)fp12;
- (void)undeleteMessages:(id)fp8;
- (void)deleteLastMessageWithHeader:(id)fp8 forHeaderKey:(id)fp12 compactWhenDone:(BOOL)fp16;
- (BOOL)allowsAppend;
- (int)undoAppendOfMessageIDs:(id)fp8;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12;
- (id)messageWithValue:(id)fp8 forHeader:(id)fp12 options:(unsigned int)fp16;
- (id)messageForMessageID:(id)fp8;
- (id)headerDataForMessage:(id)fp8;
- (id)bodyDataForMessage:(id)fp8;
- (id)fullBodyDataForMessage:(id)fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- (id)fullBodyDataForMessage:(id)fp8;
- (id)bodyForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12;
- (id)bodyForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12 updateFlags:(BOOL)fp16;
- (id)headersForMessage:(id)fp8;
- (id)headersForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12;
- (id)dataForMimePart:(id)fp8;
- (BOOL)hasCachedDataForMimePart:(id)fp8;
- (id)uniquedString:(id)fp8;
- (id)colorForMessage:(id)fp8;
- (BOOL)_shouldChangeComponentMessageFlags;
- (BOOL)_shouldChangeComponentMessageFlagsForMessage:(id)fp8;
- (id)setFlagsFromDictionary:(id)fp8 forMessages:(id)fp12;
- (id)setFlagsFromDictionary:(id)fp8 forMessage:(id)fp12;
- (void)setFlag:(id)fp8 state:(BOOL)fp12 forMessages:(id)fp16;
- (BOOL)hasUnsavedChangesToMessageData;
- (void)setColor:(id)fp8 highlightTextOnly:(BOOL)fp12 forMessages:(id)fp16;
- (void)messageColorsNeedToBeReevaluated;
- (void)startSynchronization;
- (id)_getSerialNumberString;
- (void)setNumberOfAttachments:(unsigned int)fp8 isSigned:(BOOL)fp12 isEncrypted:(BOOL)fp16 forMessage:(id)fp20;
- (void)updateNumberOfAttachmentsForMessages:(id)fp8;
- (void)updateMessageColorsSynchronouslyForMessages:(id)fp8;
- (void)updateMessageColorsAsynchronouslyForMessages:(id)fp8;
- (void)setJunkMailLevel:(int)fp8 forMessages:(id)fp12;
- (void)setJunkMailLevel:(int)fp8 forMessages:(id)fp12 trainJunkMailDatabase:(BOOL)fp16;
- (id)status;
- (void)fetchSynchronously;
- (BOOL)setPreferredEncoding:(unsigned long)fp8 forMessage:(id)fp12;
- (void)suggestSortOrder:(id)fp8 ascending:(BOOL)fp12;
- (id)sortOrder;
- (BOOL)isSortedAscending;

@end

@interface MessageStore (MessageFrameworkOnly)
+ (void)_autosaveMessageStore:(void *)fp8;
- (void)_cancelAutosave;
- (void)_setNeedsAutosave;
- (id)_fetchHeaderDataForMessage:(id)fp8;
- (id)_fetchBodyDataForMessage:(id)fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- (id)_fetchBodyForMessage:(id)fp8 updateFlags:(BOOL)fp12;
- (id)_fetchBodyForMessage:(id)fp8;
- (BOOL)_shouldCallCompactWhenClosing;
- (void)_compactMessageAtIndex:(unsigned int)fp8;
- (BOOL)_isReadyToBeInvalidated;
- (void)_saveChanges;
- (void)_invalidate;
- (void)_invalidateInBackground;
- (void)_countUnreadAndDeleted;
- (void)_cleanUpStaleAttachments;
- (id)_lockFilePath;
- (BOOL)_acquireLockFile:(id)fp8;
- (void)_removeLockFile:(id)fp8;
- (void)_flushAllCaches;
- (void)_flushAllMessageData;
- (void)_rebuildTableOfContentsSynchronously;
- (void)updateBodyFlagsForMessage:(id)fp8 body:(id)fp12;
- (id)_setOrGetBody:(id)fp8 forMessage:(id)fp12 updateFlags:(BOOL)fp16;
- (id)_setOrGetBody:(id)fp8 forMessage:(id)fp12;
- (id)_cachedBodyForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedHeadersForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedBodyDataForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedHeaderDataForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (void)updateMessageColorsSynchronouslyForMessages:(id)fp8 postingNotification:(BOOL)fp12;
- (void)updateMessages:(id)fp8 updateColor:(BOOL)fp12 updateNumberOfAttachments:(BOOL)fp16;
- (void)_setBackgroundColorForMessages:(id)fp8 textColorForMessages:(id)fp12;
- (void)_invalidateColorForMessages:(id)fp8;
- (void)_setFlagsForMessages:(id)fp8 mask:(unsigned long)fp12;
- (void)_setFlagsAndColorForMessages:(id)fp8;
- (void)messagesWereAdded:(id)fp8 forIncrementalLoading:(BOOL)fp12;
@end

@interface MessageStore (ScriptingSupport)
- (id)objectSpecifier;
- (id)objectSpecifierForMessage:(id)fp8;
@end

@interface MessageStore (ParentalControl)
- (void)setPermissionRequestState:(int)fp8 forMessage:(id)fp12;
@end

#else

@class MailboxUid;
@class MailAccount;
@class MboxIndex;
@class ObjectCache;

@interface MessageStore:NSObject
{
    @public
    struct {
        int isReadOnly:1;
        int hasUnsavedChangesToMessageData:1;
        int hasUnsavedChangesToIndex:1;
        int indexIsValid:1;
        int haveOpenLockFile:1;
        int rebuildingTOC:1;
        int compacting:1;
        int cancelInvalidation:1;
        int forceInvalidation:1;
        int isWritingChangesToDisk:1;
        int isTryingToClose:1;
        int reserved:21;
    } _flags;	// 4 = 0x4
    MailboxUid *_mailboxUid;	// 8 = 0x8
    MailAccount *_account;	// 12 = 0xc
    MboxIndex *_index;	// 16 = 0x10
    NSMutableArray *_allMessages;	// 20 = 0x14
    NSMutableArray *_messagesToBeAddedToIndex;	// 24 = 0x18
    NSMutableArray *_messagesToBeRemovedFromIndex;	// 28 = 0x1c
    unsigned int _allMessagesSize;	// 32 = 0x20
    unsigned int _deletedMessagesSize;	// 36 = 0x24
    unsigned int _deletedMessageCount;	// 40 = 0x28
    unsigned int _unreadMessageCount;	// 44 = 0x2c
    id _updateIndexMonitor;	// 48 = 0x30
    int _state;	// 52 = 0x34
    ObjectCache *_headerDataCache;	// 56 = 0x38
    ObjectCache *_headerCache;	// 60 = 0x3c
    ObjectCache *_bodyDataCache;	// 64 = 0x40
    ObjectCache *_bodyCache;	// 68 = 0x44
    NSTimer *_timer;	// 72 = 0x48
    NSMutableSet *_uniqueStrings;	// 76 = 0x4c
    double timeOfLastAutosaveOperation;	// 80 = 0x50
}

+ (void)initialize;
+ (unsigned int)numberOfCurrentlyOpenStores;
+ descriptionOfOpenStores;
+ currentlyAvailableStoreForUid:fp8;
+ currentlyAvailableStoresForAccount:fp8;
+ registerAvailableStore:fp8;
+ (void)removeStoreFromCache:fp8;
+ (char)createEmptyStoreIfNeededForPath:fp8;
+ (char)createEmptyStoreForPath:fp8;
+ (char)storeAtPathIsWritable:fp8;
+ (char)cheapStoreAtPathIsEmpty:fp8;
+ (int)copyMessages:fp8 toMailboxUid:fp12 shouldDelete:(char)fp16;
- (void)release;
- initWithMailboxUid:fp8 readOnly:(char)fp12;
- copyWithZone:(struct _NSZone *)fp8;
- (void)dealloc;
- (void)openAsynchronouslyUpdatingIndex:(char)fp8 andOtherMetadata:(char)fp12;
- (void)openAsynchronously;
- (void)openSynchronously;
- (void)openSynchronouslyUpdatingIndex:(char)fp8 andOtherMetadata:(char)fp12;
- (void)updateMetadataAsynchronously;
- (void)updateMetadata;
- (void)didOpen;
- (void)writeUpdatedMessageDataToDisk;
- (void)invalidateSavingChanges:(char)fp8;
- account;
- mailboxUid;
- (char)isOpened;
- storePathRelativeToAccount;
- displayName;
- (const STR)displayNameForLogging;
- (char)isReadOnly;
- description;
- (char)isTrash;
- (char)isDrafts;
- (void)messageFlagsDidChange:fp8 flags:fp12;
- (void)structureDidChange;
- (void)messagesWereAdded:fp8;
- (void)messagesWereCompacted:fp8;
- (void)updateUserInfoToLatestValues;
- (unsigned int)totalMessageSize;
- (void)deletedCount:(unsigned int *)fp8 andSize:(unsigned int *)fp12;
- (unsigned int)totalCount;
- (unsigned int)unreadCount;
- (unsigned int)indexOfMessage:fp8;
- copyOfAllMessages;
- mutableCopyOfAllMessages;
- (void)addMessagesToAllMessages:fp8;
- (void)addMessageToAllMessages:fp8;
- _defaultRouterDestination;
- routeMessages:fp8;
- finishRoutingMessages:fp8 routed:fp12;
- (char)canRebuild;
- (void)rebuildTableOfContentsAsynchronously;
- (char)canCompact;
- (void)doCompact;
- (void)deleteMessagesOlderThanNumberOfDays:(int)fp8 compact:(char)fp12;
- (void)deleteMessages:fp8 moveToTrash:(char)fp12;
- (void)undeleteMessages:fp8;
- (void)deleteLastMessageWithHeader:fp8 forHeaderKey:fp12 compactWhenDone:(char)fp16;
- (char)allowsAppend;
- (int)undoAppendOfMessageIDs:fp8;
- (int)appendMessages:fp8 unsuccessfulOnes:fp12 newMessageIDs:fp16;
- (int)appendMessages:fp8 unsuccessfulOnes:fp12;
- messageWithValue:fp8 forHeader:fp12 options:(unsigned int)fp16;
- messageForMessageID:fp8;
- (void)_setHeaderDataInCache:fp8 forMessage:fp12;
- headerDataForMessage:fp8;
- bodyDataForMessage:fp8;
- fullBodyDataForMessage:fp8;
- bodyForMessage:fp8 fetchIfNotAvailable:(char)fp12;
- headersForMessage:fp8;
- dataForMimePart:fp8;
- (char)hasCachedDataForMimePart:fp8;
- uniquedString:fp8;
- colorForMessage:fp8;
- (char)_shouldChangeComponentMessageFlags;
- setFlagsFromDictionary:fp8 forMessages:fp12;
- setFlagsFromDictionary:fp8 forMessage:fp12;
- (void)setFlag:fp8 state:(char)fp12 forMessages:fp16;
- (void)setColor:fp8 highlightTextOnly:(char)fp12 forMessages:fp16;
- (void)messageColorsNeedToBeReevaluated;
- (void)startSynchronization;
- performBruteForceSearchWithString:fp8 options:(int)fp12;
- (STR)createSerialNumberStringFrom:(STR)fp8 colorCode:(unsigned short)fp12;
- _getSerialNumberString;
- (void)setNumberOfAttachments:(unsigned int)fp8 isSigned:(char)fp12 isEncrypted:(char)fp16 forMessage:fp20;
- (void)updateNumberOfAttachmentsForMessages:fp8;
- (void)updateMessageColorsSynchronouslyForMessages:fp8;
- (void)updateMessageColorsAsynchronouslyForMessages:fp8;
- (void)setJunkMailLevel:(int)fp8 forMessages:fp12;
- (void)setJunkMailLevel:(int)fp8 forMessages:fp12 trainJunkMailDatabase:(char)fp16;
- status;
- (void)fetchSynchronously;
- (char)setPreferredEncoding:(unsigned long)fp8 forMessage:fp12;
- (void)suggestSortOrder:fp8 ascending:(char)fp12;
- sortOrder;
- (char)isSortedAscending;

@end

@interface MessageStore(MessageFrameworkOnly)
+ (void)_autosaveMessageStore:(void *)fp8;
- (void)_cancelAutosave;
- (void)_setNeedsAutosave;
- _fetchHeaderDataForMessage:fp8;
- _fetchBodyDataForMessage:fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- _fetchBodyForMessage:fp8;
- (char)_shouldCallCompactWhenClosing;
- (void)_compactMessageAtIndex:(unsigned int)fp8;
- (char)_isReadyToBeInvalidated;
- (void)_saveChanges;
- (void)_invalidate;
- (void)_invalidateInBackground;
- (void)_countUnreadAndDeleted;
- (void)_cleanUpStaleAttachments;
- _lockFilePath;
- (char)_acquireLockFile:fp8;
- (void)_removeLockFile:fp8;
- (void)_flushAllMessageData;
- (void)_rebuildTableOfContentsSynchronously;
- _setOrGetBody:fp8 forMessage:fp12;
- (void)updateMessageColorsSynchronouslyForMessages:fp8 postingNotification:(char)fp12;
@end

@interface MessageStore(Indexing)
- (char)allowsIndexing;
- (char)isIndexed;
- (char)indexIsValid;
- (void)updateIndex;
- _index;
- (void)openIndexWithWriteAccess:(char)fp8;
- (void)checkForValidIndex;
- (void)closeIndex;
- (void)_fullUpdateIndexAsynchronously;
- (void)_setNeedsToUpdateIndex;
- (void)_addMessagesToIndex:fp8;
- (void)_removeMessagesFromIndex:fp8;
- (void)stopUpdatingIndex;
- (void)handleUpdatingFinished;
- (void)_prepareIndexForUpdate;
- (void)_updateIndex;
- (void)_fullUpdateOfIndex;
- (void)_writeUpdatedIndexToDisk;
- indexedSearchFor:fp8 ranks:(id *)fp12 errorString:(id *)fp16;
- cheapIndexedSearchFor:fp8 ranks:(id *)fp12 errorString:(id *)fp16;
- (void)invalidateIndex;
- (void)_invalidateIndex;
- (char)_isUpdatingIndex;
@end

@interface MessageStore(ScriptingSupport)
- objectSpecifier;
- objectSpecifierForMessage:fp8;
@end

#endif
